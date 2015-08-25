#ifndef COMMAND_LD_H
#define COMMAND_LD_H

#include "command.hpp"

class commandLoad: public command {
public:
    commandLoad(std::ofstream *o) { outStream = o; };
    commandLoad(memory *i) { svmMemory = i; };
    std::string name() { return "ld"; };
    mnemonic_t mnemonic_code() { return 12; };
    unsigned int operand_size() { return 4; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, address_t C);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
