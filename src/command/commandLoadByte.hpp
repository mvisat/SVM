#ifndef COMMAND_LB_H
#define COMMAND_LB_H

#include "command.hpp"

class commandLoadByte: public command {
public:
    commandLoadByte(std::ofstream *o) { outStream = o; };
    commandLoadByte(memory *i) { svmMemory = i; };
    std::string name() { return "lb"; };
    mnemonic_t mnemonic_code() { return 13; };
    unsigned int operand_size() { return 4; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, address_t C);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
