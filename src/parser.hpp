#ifndef PARSER_H
#define PARSER_H

#include "svm_exception.hpp"
#include "typedef.hpp"
#include "strutil.hpp"
#include "memory.hpp"

using namespace std;

int parseRegister(const string& s);
constant_t parseConstant(const string& s);

#endif
