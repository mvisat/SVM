#ifndef COMMAND_LOPEN_H
#define COMMAND_LOPEN_H

#include "command.hpp"

class commandLibraryOpen: public command {
public:
    commandLibraryOpen(std::ofstream *o) { outStream = o; };
    commandLibraryOpen(memory *i) { svmMemory = i; };
    std::string name() { return "lopen"; };
    mnemonic_t mnemonic_code() { return 24; };
    unsigned int operand_size() { return 2; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(const std::string& lib_name);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
