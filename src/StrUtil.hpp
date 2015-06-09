#ifndef STR_UTIL_H
#define STR_UTIL_H

#include <sstream>
#include <vector>

using namespace std;

string StrTrim(const string &s);
string StrTrimLeft(const string &s);
string StrTrimRight(const string &s);
vector<string> StrSplit(const string &s, char delim);
vector<string> StrSplitByWhitespace(const string& s);
int StrToInt(const string &s);

#endif
