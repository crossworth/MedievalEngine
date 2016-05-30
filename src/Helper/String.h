#ifndef STRING_H
#define STRING_H
#include <string>
#include <sstream>
#include <cstdlib>
#include <clocale>
#include "Helper/OS.h"

namespace ME {

class String {
public:

	static std::wstring string_to_wstring(const std::string& string);
    static std::string wstring_to_string(const std::wstring& string);

	String();
	String(const std::string& string);
    String(const std::wstring& string);

    std::size_t getSize();

    void clear();

    void insert(std::size_t position, const String& string);
    void insert(std::size_t position, const std::string& string);
    void insert(std::size_t position, const std::wstring& string);
    void insert(std::size_t position, const uint32_t& unicode);

    void erase(std::size_t position, std::size_t count = 1);

	std::string getString() const;
	std::wstring getWideString() const;

	void operator=(const String& string) { 
        mString = string.mString;
    }

    String& operator=(const std::string& string) { 
        mString = string;
        return *this;
    }

    String& operator=(const std::wstring& string) {
        mString = String::wstring_to_string(string);
        return *this;
    }

    inline bool operator==(const String& other) {
        return (mString == other.mString);
	}

	inline bool operator==(const std::string& other) {
        return (mString == other);
	}

	inline bool operator!=(const String& other) {
        return !(*this == other);
    }

    inline bool operator!=(const std::string& other) {
        return !(*this == other);
    }

    inline String operator+(const String& other) {
        std::string tmp = this->mString + other.mString;
        return String(tmp);
    }

    inline String operator+(const std::string& string) {
        std::string tmp = this->mString + string;
        return String(tmp);
    }

    inline String operator+(const char* string) {
        std::string tmp = this->mString + std::string(string);
        return String(tmp);
    }

    friend String operator+(const char* lhs, const String& rhs) { 
        return String(std::string(lhs) + rhs.mString);
    }

    operator std::string() const { 
    	return this->getString();
    }

    operator std::wstring() const { 
        return this->getWideString();
    }

private:
	std::string mString;
};

}

std::ostream& operator<<(std::ostream& string, ME::String& other);

#endif // STRING_H