#include "commandLibraryLink.hpp"

void commandLibraryLink::execute(const vector<string>& cmd) {
    string function_name = cmd[1];
    execute(function_name);
}

void commandLibraryLink::execute(const vector<opcode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    pointer = pointer + 1;
    string function_name = "";
    while (cmd[pointer] != 0)
        function_name += cmd[pointer++];
    execute(function_name);
    svmMemory->set_program_counter(pointer+1);
}

void commandLibraryLink::execute(const string& function_name) {
    svmMemory->link_lib_function(function_name);
}

void commandLibraryLink::write_bytecode(const vector<string>& cmd) {
    string function_name = cmd[1];
    vector<char> code;
    code.push_back(opcode());
    for (unsigned int i = 0; i < function_name.size(); ++i)
        code.push_back(function_name[i]);
    code.push_back(0);
    outStream->write(code.data(), code.size());
}
