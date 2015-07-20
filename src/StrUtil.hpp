#ifndef STR_UTIL_H
#define STR_UTIL_H

#include <sstream>
#include <vector>
#include <typeinfo>

using namespace std;

string strTrim(const string &s);
string strTrimLeft(const string &s);
string strTrimRight(const string &s);
vector<string> strSplit(const string &s, char delim);
vector<string> strSplitByWhitespace(const string& s);

template <typename T>
T strConvert(const std::string& s) {
    stringstream ss(s);

    T result;
    if ((ss >> result).fail() || !(ss >> std::ws).eof())
        throw std::bad_cast();

    return result;
}

#endif
