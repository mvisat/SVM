#include "commandLibraryOpen.hpp"

void commandLibraryOpen::execute(const std::vector<std::string>& cmd) {
    if (!svmMemory->get_start()) {
        std::string lib_name = cmd[1];
        execute(lib_name);
    }
    svmMemory->inc_program_counter();
}

void commandLibraryOpen::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (!svmMemory->get_start()) {
        std::string lib_name;
        while (cmd[++pointer] != 0)
            lib_name += cmd[pointer];
        execute(lib_name);
    }
    else
        while (cmd[++pointer] != 0);
    svmMemory->set_program_counter(pointer+1);
}

void commandLibraryOpen::execute(const std::string& lib_name) {
    svmMemory->load_lib(lib_name);
}

void commandLibraryOpen::write_bytecode(const std::vector<std::string>& cmd) {
    std::string lib_name = cmd[1];
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    for (unsigned int i = 0; i < lib_name.size(); ++i)
        bytecode.push_back(lib_name[i]);
    bytecode.push_back(0);
    outStream->write(bytecode.data(), bytecode.size());
}
