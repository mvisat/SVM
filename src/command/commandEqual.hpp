#ifndef COMMAND_EQ_H
#define COMMAND_EQ_H

#include "command.hpp"

class commandEqual: public command {
public:
    commandEqual(std::ofstream *o) { outStream = o; }
    commandEqual(memory *i) { svmMemory = i; }
    std::string name() { return "eq"; }
    mnemonic_t mnemonic_code() { return 9; }
    unsigned int operand_size() { return 4; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
