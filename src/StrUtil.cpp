#include "StrUtil.hpp"

string StrTrim(const string &s) {
    return StrTrimLeft(StrTrimRight(s));
}

string StrTrimLeft(const string &s) {
    size_t startpos = s.find_first_not_of(" \t");
    if (string::npos != startpos)
        return s.substr(startpos);
    else
        return s;
}

string StrTrimRight(const string& s) {
    size_t endpos = s.find_last_not_of(" \t");
    if (string::npos != endpos)
        return s.substr(0, endpos+1);
    else
        return s;
}

vector<string> StrSplit(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

vector<string> StrSplitByWhitespace(const string& s) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (ss >> item)
        elems.push_back(item);
    return elems;
}

int StrToInt(const string& s) {
    stringstream ss(s);
    int val;
    ss >> val;
    return val;
}
