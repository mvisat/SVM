#ifndef COMMAND_ADDI_H
#define COMMAND_ADDI_H

#include "command.hpp"

class commandAddImmediate: public command {
public:
    commandAddImmediate(std::ofstream *o) { outStream = o; }
    commandAddImmediate(memory *i) { svmMemory = i; }
    std::string name() { return "addi"; }
    mnemonic_t mnemonic_code() { return 3; }
    unsigned int operand_size() { return 4; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, register_t C);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
