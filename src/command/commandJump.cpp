#include "commandJump.hpp"

void commandJump::execute(const std::vector<std::string>& cmd) {
    if (svmMemory->get_start()) {
        std::string label = cmd[1];
        execute(svmMemory->get_label(label));
    }
    svmMemory->inc_program_counter();
}

void commandJump::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (svmMemory->get_start()) {
        pointer = pointer + 1;
        counter_t address = 0;
        for (unsigned int i = 0; i < sizeof(counter_t); ++i) {
            address = address | (cmd[pointer+i] << (i << 3));
        }
        execute(address);
    }
    else
        svmMemory->set_program_counter(pointer+sizeof(counter_t)+1);
}

void commandJump::execute(counter_t address) {
    svmMemory->set_program_counter(address);
}

void commandJump::write_bytecode(const std::vector<std::string>& cmd) {
    std::string label = cmd[1];
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    for (unsigned int i = 0; i < sizeof(counter_t); ++i)
        bytecode.push_back(0);
    outStream->write(bytecode.data(), bytecode.size());
    counter_t jumpAddress = outStream->tellp();
    (*jumpTable)[label].push_back(jumpAddress-sizeof(counter_t));
}
