#ifndef PARSER_H
#define PARSER_H

#include "svm_exception.hpp"
#include "typedef.hpp"
#include "strutil.hpp"
#include "memory.hpp"

#include <fstream>

using namespace std;

vector<vector<string> > parse_file(const string& file);
int parse_register(const string& s);
constant_t parse_constant(const string& s);

#endif
