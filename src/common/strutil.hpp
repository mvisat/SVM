#ifndef COMMON_STRUTIL_H
#define COMMON_STRUTIL_H

#include <iomanip>
#include <sstream>
#include <vector>
#include <typeinfo>

std::string str_trim(const std::string &s);
std::string str_trim_left(const std::string &s);
std::string str_trim_right(const std::string &s);

std::vector<std::string> str_split(const std::string &s, char delim);
std::vector<std::string> str_split_ws(const std::string& s);

std::string str_find_ext(const std::string& s);
std::string str_replace_ext(const std::string& s, const std::string& ext);

template <typename T>
T from_string(const std::string& s) {
    std::stringstream ss(s);

    T result;
    if ((ss >> result).fail() || !(ss >> std::ws).eof())
        throw std::bad_cast();

    return result;
}

template <typename T>
std::string to_string(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template <typename T>
std::string to_hex(const T& t) {
    std::stringstream ss;
    ss << std::hex << t;
    return ss.str();
}

#endif
