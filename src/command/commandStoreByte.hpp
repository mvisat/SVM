#ifndef COMMAND_STB_H
#define COMMAND_STB_H

#include "command.hpp"

class commandStoreByte: public command {
public:
    commandStoreByte(std::ofstream *o) { outStream = o; };
    commandStoreByte(memory *i) { svmMemory = i; };
    std::string name() { return "stb"; };
    mnemonic_t mnemonic_code() { return 16; };
    unsigned int operand_size() { return 4; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, address_t C);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
