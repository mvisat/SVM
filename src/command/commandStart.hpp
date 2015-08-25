#ifndef COMMAND_START_H
#define COMMAND_START_H

#include "command.hpp"

class commandStart: public command {
public:
    commandStart(std::ofstream *o) { outStream = o; };
    commandStart(memory *i) { svmMemory = i; };
    std::string name() { return "start"; };
    mnemonic_t mnemonic_code() { return 1; };
    unsigned int operand_size() { return 1; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute();
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
