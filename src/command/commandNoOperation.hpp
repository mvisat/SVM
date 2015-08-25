#ifndef COMMAND_NOP_H
#define COMMAND_NOP_H

#include "command.hpp"

class commandNoOperation: public command {
public:
    commandNoOperation(std::ofstream *o) { outStream = o; };
    commandNoOperation(memory *i) { svmMemory = i; };
    std::string name() { return "nop"; };
    mnemonic_t mnemonic_code() { return 0; };
    unsigned int operand_size() { return 1; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute();
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
