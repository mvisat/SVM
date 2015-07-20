#include "strutil.hpp"

string strTrim(const string &s) {
    return strTrimLeft(strTrimRight(s));
}

string strTrimLeft(const string &s) {
    size_t startpos = s.find_first_not_of(" \t");
    if (string::npos != startpos)
        return s.substr(startpos);
    else
        return s;
}

string strTrimRight(const string& s) {
    size_t endpos = s.find_last_not_of(" \t");
    if (string::npos != endpos)
        return s.substr(0, endpos+1);
    else
        return s;
}

vector<string> strSplit(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

vector<string> strSplitByWhitespace(const string& s) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (ss >> item)
        elems.push_back(item);
    return elems;
}
