#ifndef COMMAND_LINK_H
#define COMMAND_LINK_H

#include "command.hpp"

class commandLibraryLink: public command {
public:
    commandLibraryLink(std::ofstream *o) { outStream = o; };
    commandLibraryLink(memory *i) { svmMemory = i; };
    std::string name() { return "link"; };
    mnemonic_t mnemonic_code() { return 25; };
    unsigned int operand_size() { return 2; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(const std::string& function_name);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
