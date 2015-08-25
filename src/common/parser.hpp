#ifndef COMMON_PARSER_H
#define COMMON_PARSER_H

#include "svm_exception.hpp"
#include "typedef.hpp"
#include "strutil.hpp"
#include "memory.hpp"

#include <fstream>

std::vector<std::vector<std::string> > parse_file(const std::string& file);
int parse_register(const std::string& s);
constant_t parse_constant(const std::string& s);
std::string parse_function(const std::string& s);

#endif
