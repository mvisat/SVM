#ifndef COMMAND_LDI_H
#define COMMAND_LDI_H

#include "command.hpp"

class commandLoadImmediate: public command {
public:
    commandLoadImmediate(std::ofstream *o) { outStream = o; };
    commandLoadImmediate(memory *i) { svmMemory = i; };
    std::string name() { return "ldi"; };
    mnemonic_t mnemonic_code() { return 14; };
    unsigned int operand_size() { return 3; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, register_t C);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
