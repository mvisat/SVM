#include "strutil.hpp"

std::string str_trim(const std::string &s) {
    return str_trim_left(str_trim_right(s));
}

std::string str_trim_left(const std::string &s) {
    size_t startpos = s.find_first_not_of(" \t");
    if (std::string::npos != startpos)
        return s.substr(startpos);
    else
        return s;
}

std::string str_trim_right(const std::string& s) {
    size_t endpos = s.find_last_not_of(" \t");
    if (std::string::npos != endpos)
        return s.substr(0, endpos+1);
    else
        return s;
}

std::vector<std::string> str_split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

std::vector<std::string> str_split_ws(const std::string& s) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (ss >> item)
        elems.push_back(item);
    return elems;
}

std::string str_replace_ext(const std::string& s, const std::string& ext) {
    std::string new_filename = s;
    size_t result = new_filename.find_last_of('.');

    if (std::string::npos != result)
        new_filename.erase(result);

    return new_filename.append("." + ext);
}

std::string str_find_ext(const std::string& s) {
    return s.substr(s.find_last_of('.')+1);
}
