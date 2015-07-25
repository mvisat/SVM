#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <stdint.h>

using namespace std;

typedef uint8_t index_t;
typedef int16_t register_t;
typedef int16_t constant_t;
typedef int8_t memory_t;
typedef uint16_t address_t;
typedef uint64_t counter_t;
typedef char opcode_t;
const int OPCODE_MAX = 0xFF;
const int KEI_HEADER_SIZE = 12;

#endif
