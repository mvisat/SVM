#ifndef COMMAND_LT_H
#define COMMAND_LT_H

#include "command.hpp"

class commandLessThan: public command {
public:
    commandLessThan(std::ofstream *o) { outStream = o; };
    commandLessThan(memory *i) { svmMemory = i; };
    std::string name() { return "lt"; };
    mnemonic_t mnemonic_code() { return 10; };
    unsigned int operand_size() { return 4; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
