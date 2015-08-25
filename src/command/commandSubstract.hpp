#ifndef COMMAND_SUB_H
#define COMMAND_SUB_H

#include "command.hpp"

class commandSubstract: public command {
public:
    commandSubstract(std::ofstream *o) { outStream = o; };
    commandSubstract(memory *i) { svmMemory = i; };
    std::string name() { return "sub"; };
    mnemonic_t mnemonic_code() { return 4; };
    unsigned int operand_size() { return 4; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
