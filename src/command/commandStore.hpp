#ifndef COMMAND_STR_H
#define COMMAND_STR_H

#include "command.hpp"

class commandStore: public command {
public:
    commandStore(std::ofstream *o) { outStream = o; };
    commandStore(memory *i) { svmMemory = i; };
    std::string name() { return "str"; };
    mnemonic_t mnemonic_code() { return 15; };
    unsigned int operand_size() { return 4; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, address_t C);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
