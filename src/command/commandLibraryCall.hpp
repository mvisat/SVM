#ifndef COMMAND_LIBC_H
#define COMMAND_LIBC_H

#include "command.hpp"

#include <iostream>



class commandLibraryCall: public command {
public:
    commandLibraryCall(std::ofstream *o) { outStream = o; };
    commandLibraryCall(memory *i) { svmMemory = i; };
    std::string name() { return "libc"; };
    mnemonic_t mnemonic_code() { return 22; };
    unsigned int operand_size() { return 4; };
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, const std::string& func);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
