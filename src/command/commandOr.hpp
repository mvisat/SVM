#ifndef COMMAND_OR_H
#define COMMAND_OR_H

#include "command.hpp"

class commandOr: public command {
public:
    commandOr(std::ofstream *o) { outStream = o; };
    commandOr(memory *i) { svmMemory = i; };
    std::string name() { return "or"; };
    mnemonic_t mnemonic_code() { return 7; };
    unsigned int operand_size() { return 4; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
