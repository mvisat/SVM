#include "commandLibraryLink.hpp"

void commandLibraryLink::execute(const std::vector<std::string>& cmd) {
    if (!svmMemory->get_start()) {
        std::string function_name = parse_function(cmd[1]);
        execute(function_name);
    }
    svmMemory->inc_program_counter();
}

void commandLibraryLink::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (!svmMemory->get_start()) {
        pointer = pointer + 1;
        std::string function_name;
        while (cmd[pointer] != 0)
            function_name += cmd[pointer++];
        execute(parse_function(function_name));
    }
    else {
        while (cmd[++pointer] != 0);
    }
    svmMemory->set_program_counter(pointer+1);
}

void commandLibraryLink::execute(const std::string& function_name) {
    svmMemory->link_lib_function(function_name);
}

void commandLibraryLink::write_bytecode(const std::vector<std::string>& cmd) {
    std::string function_name = cmd[1];
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    for (unsigned int i = 0; i < function_name.size(); ++i)
        bytecode.push_back(function_name[i]);
    bytecode.push_back(0);
    outStream->write(bytecode.data(), bytecode.size());
}
