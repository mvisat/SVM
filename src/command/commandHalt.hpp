#ifndef COMMAND_HALT_H
#define COMMAND_HALT_H

#include "command.hpp"

class commandHalt: public command {
public:
    commandHalt(std::ofstream *o) { outStream = o; }
    commandHalt(memory *i) { svmMemory = i; }
    std::string name() { return "halt"; }
    mnemonic_t mnemonic_code() { return 23; }
    unsigned int operand_size() { return 1; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute();
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
