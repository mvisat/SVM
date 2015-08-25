#ifndef COMMAND_ADD_H
#define COMMAND_ADD_H

#include "command.hpp"

class commandAdd: public command {
public:
    commandAdd(std::ofstream *o) { outStream = o; };
    commandAdd(memory *i) { svmMemory = i; };
    std::string name() { return "add"; };
    mnemonic_t mnemonic_code() { return 2; };
    unsigned int operand_size() { return 4; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
