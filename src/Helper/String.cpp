#include "String.h"

using namespace ME;

size_t String::npos = -1;

String::String() {
	mString = "";
}

std::size_t String::getSize() {
    return mString.length();
}

void String::clear() {
    mString.clear();
}

std::vector<String> String::explode(const char& delimiter) {
    std::vector<String> result;
    std::istringstream iss(mString);

    for (std::string token; std::getline(iss, token, delimiter); ) {
        result.push_back(String(std::move(token)));
    }

    return result;
}

String String::substr(size_t pos, size_t len) {
    std::string tmp;

    if (len == String::npos) {
        tmp = mString.substr(pos);
    } else {
        tmp = mString.substr(pos, len);
    }

    return String(tmp);
}

void String::insert(std::size_t position, const String& string) {
    mString.insert(position, string.getString());
}

void String::insert(std::size_t position, const std::string& string) {
    mString.insert(position, string);
}

void String::insert(std::size_t position, const std::wstring& string) {
    mString.insert(position, String::wstring_to_string(string));
}

void String::insert(std::size_t position, const uint32_t& unicode) {
    char code = (char) unicode;
    std::string str;
    str = code;
    mString.insert(position, str);
}

void String::removeNewLine() {
    mString.erase(std::remove(mString.begin(), mString.end(), '\n'), mString.end());
}

void String::removeCarriageReturn() {
    mString.erase(std::remove(mString.begin(), mString.end(), '\r'), mString.end());   
}

void String::removeTab() {
    mString.erase(std::remove(mString.begin(), mString.end(), '\t'), mString.end());
}

void String::erase(std::size_t position, std::size_t count) {
    mString.erase(position, count);
}

String::String(const std::string& string) {
	mString = string;
}

String::String(const std::wstring& string) {
    mString = String::wstring_to_string(string);
}

std::wstring String::getWideString() const {
	return String::string_to_wstring(mString);
}

std::string String::getString() const {
    return mString;
}

std::ostream& operator<<(std::ostream& string, ME::String& other) { 
	string << other.getString();
	return string;
}

/**
* From on https://github.com/niangaotuantuan/string2wstring
* If set the locale to Portuguese work as well, since Im using Portuguese to test
* UTF-8 is a better way to to do so, but we could use getenv(LC_CTYPE) or something like that
* Boost seens to be using it 
* https://github.com/boostorg/locale/blob/7cfa65b2b8114afe44c7a950553620133cd5df15/src/util/default_locale.cpp
* TODO(Pedro): Probability wont work on Windows
**/
std::wstring String::string_to_wstring(const std::string& string) {
    std::setlocale(LC_ALL, "UTF-8"); 

    const char* source   = string.c_str();
    size_t destSize      = string.size() + 1;
    wchar_t* destination = new wchar_t[destSize];

    std::wmemset(destination, 0, destSize);
    std::mbstowcs(destination,source,destSize);

    std::wstring result = destination;
    delete[] destination;

    setlocale(LC_ALL, "C");

    return result;
}

std::string String::wstring_to_string(const std::wstring& string) {
    std::string curLocale = setlocale(LC_ALL, NULL);

    setlocale(LC_ALL, "UTF-8");

    const wchar_t* source = string.c_str();
    size_t destSize       = 2 * string.size() + 1;
    char* destination     = new char[destSize];

    memset(destination,0,destSize);
    wcstombs(destination,source,destSize);

    std::string result = destination;
    delete[] destination;

    setlocale(LC_ALL, curLocale.c_str());

    return result;
}


std::string String::wstring_to_UTF8(const std::wstring& string) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToUTF8;
    return wideToUTF8.to_bytes(string);
}

std::wstring String::UTF8_to_wstring(const std::string& string) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> UTF8ToWide;
    return UTF8ToWide.from_bytes(string);
}