// The MIT License (MIT) 

// Copyright (c) 2013-2016 Rapptz, ThePhD and contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef SOL_PROTECTED_FUNCTION_RESULT_HPP
#define SOL_PROTECTED_FUNCTION_RESULT_HPP

#include "reference.hpp"
#include "tuple.hpp"
#include "stack.hpp"
#include "proxy_base.hpp"
#include <cstdint>

namespace sol {
struct protected_function_result : public proxy_base<protected_function_result> {
private:
    lua_State* L;
    int index;
    int returncount;
    int popcount;
    call_status err;

    template <typename T>
    decltype(auto) tagged_get( types<sol::optional<T>> ) const {
        if (!valid()) {
            return sol::optional<T>(nullopt);
        }
        return stack::get<sol::optional<T>>(L, index);
    }

    template <typename T>
    decltype(auto) tagged_get( types<T> ) const {
#ifdef SOL_CHECK_ARGUMENTS
        if (!valid()) {
            type_panic(L, index, type_of(L, index), type::none);
        }
#endif // Check Argument Safety
        return stack::get<T>(L, index);
    }

    sol::optional<sol::error> tagged_get( types<sol::optional<sol::error>> ) const {
        if (valid()) {
            return nullopt;
        }
        return sol::error(detail::direct_error, stack::get<std::string>(L, index));
    }

    sol::error tagged_get( types<sol::error> ) const {
#ifdef SOL_CHECK_ARGUMENTS
        if (valid()) {
            type_panic(L, index, type_of(L, index), type::none);
        }
#endif // Check Argument Safety
        return sol::error(detail::direct_error, stack::get<std::string>(L, index));
    }

public:
    protected_function_result() = default;
    protected_function_result(lua_State* L, int index = -1, int returncount = 0, int popcount = 0, call_status err = call_status::ok): L(L), index(index), returncount(returncount), popcount(popcount), err(err) {
        
    }
    protected_function_result(const protected_function_result&) = default;
    protected_function_result& operator=(const protected_function_result&) = default;
    protected_function_result(protected_function_result&& o) : L(o.L), index(o.index), returncount(o.returncount), popcount(o.popcount), err(o.err) {
        // Must be manual, otherwise destructor will screw us
        // return count being 0 is enough to keep things clean
        // but we will be thorough
        o.L = nullptr;
        o.index = 0;
        o.returncount = 0;
        o.popcount = 0;
        o.err = call_status::runtime;
    }
    protected_function_result& operator=(protected_function_result&& o) {
        L = o.L;
        index = o.index;
        returncount = o.returncount;
        popcount = o.popcount;
        err = o.err;
        // Must be manual, otherwise destructor will screw us
        // return count being 0 is enough to keep things clean
        // but we will be thorough
        o.L = nullptr;
        o.index = 0;
        o.returncount = 0;
        o.popcount = 0;
        o.err = call_status::runtime;
        return *this;
    }

    call_status error() const {
        return err;
    }

    bool valid() const {
        return error() == call_status::ok || error() == call_status::yielded;
    }

    template<typename T>
    T get() const {
        return tagged_get(types<meta::Unqualified<T>>());
    }

    lua_State* lua_state() const { return L; };
    int stack_index() const { return index; };

    ~protected_function_result() {
        stack::remove(L, index, popcount);
    }
};
} // sol

#endif // SOL_PROTECTED_FUNCTION_RESULT_HPP
