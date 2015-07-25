#ifndef STR_UTIL_H
#define STR_UTIL_H

#include <iomanip>
#include <sstream>
#include <vector>
#include <typeinfo>

using namespace std;

string str_trim(const string &s);
string str_trim_left(const string &s);
string str_trim_right(const string &s);

vector<string> str_split(const string &s, char delim);
vector<string> str_split_ws(const string& s);

string str_replace_ext(const string& s, const string& ext);

template <typename T>
T from_string(const std::string& s) {
    stringstream ss(s);

    T result;
    if ((ss >> result).fail() || !(ss >> std::ws).eof())
        throw std::bad_cast();

    return result;
}

template <typename T>
string to_string(const T& t) {
    stringstream ss;
    ss << t;
    return ss.str();
}

template <typename T>
string to_hex(const T& t) {
    stringstream ss;
    ss << std::hex << t;
    return ss.str();
}

#endif
