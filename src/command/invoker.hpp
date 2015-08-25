#ifndef COMMAND_INVOKER_H
#define COMMAND_INVOKER_H

#include "command.hpp"

#include <map>
#include <iostream>

class invoker {
public:
    invoker();

    void add(command *c);
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd, counter_t pointer);
    void write_bytecode(const std::vector<std::string>& cmd);
private:
    std::map<std::string, command*> mapOfCommandName;
    std::vector<command*> mapOfCommandCode;
};

#endif
