#ifndef COMMAND_NOT_H
#define COMMAND_NOT_H

#include "command.hpp"

class commandNot: public command {
public:
    commandNot(std::ofstream *o) { outStream = o; };
    commandNot(memory *i) { svmMemory = i; };
    std::string name() { return "not"; };
    mnemonic_t mnemonic_code() { return 8; };
    unsigned int operand_size() { return 3; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
