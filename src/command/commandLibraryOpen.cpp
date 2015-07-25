#include "commandLibraryOpen.hpp"

void commandLibraryOpen::execute(const vector<string>& cmd) {
    string lib_name = cmd[1];
    execute(lib_name);
}

void commandLibraryOpen::execute(const vector<opcode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    pointer = pointer + 1;
    string lib_name;
    while (cmd[pointer] != 0)
        lib_name += cmd[pointer++];
    execute(lib_name);
    svmMemory->set_program_counter(pointer+1);
}

void commandLibraryOpen::execute(const string& lib_name) {
    svmMemory->load_lib(lib_name);
}

void commandLibraryOpen::write_bytecode(const vector<string>& cmd) {
    string lib_name = cmd[1];
    vector<char> code;
    code.push_back(opcode());
    for (unsigned int i = 0; i < lib_name.size(); ++i)
        code.push_back(lib_name[i]);
    code.push_back(0);
    outStream->write(code.data(), code.size());
}
