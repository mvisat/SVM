#ifndef COMMAND_AND_H
#define COMMAND_AND_H

#include "command.hpp"

class commandAnd: public command {
public:
    commandAnd(std::ofstream *o) { outStream = o; }
    commandAnd(memory *i) { svmMemory = i; }
    std::string name() { return "and"; }
    mnemonic_t mnemonic_code() { return 6; }
    unsigned int operand_size() { return 4; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
