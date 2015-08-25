#ifndef COMMAND_GT_H
#define COMMAND_GT_H

#include "command.hpp"

class commandGreaterThan: public command {
public:
    commandGreaterThan(std::ofstream *o) { outStream = o; }
    commandGreaterThan(memory *i) { svmMemory = i; }
    std::string name() { return "gt"; }
    mnemonic_t mnemonic_code() { return 11; }
    unsigned int operand_size() { return 4; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
