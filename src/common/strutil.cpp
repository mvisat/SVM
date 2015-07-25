#include "strutil.hpp"

string str_trim(const string &s) {
    return str_trim_left(str_trim_right(s));
}

string str_trim_left(const string &s) {
    size_t startpos = s.find_first_not_of(" \t");
    if (string::npos != startpos)
        return s.substr(startpos);
    else
        return s;
}

string str_trim_right(const string& s) {
    size_t endpos = s.find_last_not_of(" \t");
    if (string::npos != endpos)
        return s.substr(0, endpos+1);
    else
        return s;
}

vector<string> str_split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

vector<string> str_split_ws(const string& s) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (ss >> item)
        elems.push_back(item);
    return elems;
}

string str_replace_ext(const string& s, const string& ext) {
    std::string new_filename = s;
    size_t result = new_filename.find_last_of('.');

    if (std::string::npos != result)
        new_filename.erase(result);

    return new_filename.append("." + ext);
}
