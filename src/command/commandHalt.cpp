#include "commandHalt.hpp"

void commandHalt::execute(const std::vector<std::string>& cmd) {
    if (svmMemory->get_start())
        execute();
    svmMemory->inc_program_counter();
}

void commandHalt::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (svmMemory->get_start())
        execute();
    svmMemory->set_program_counter(pointer+1);
}

void commandHalt::execute() {
    svmMemory->set_halt();
}

void commandHalt::write_bytecode(const std::vector<std::string>& cmd) {
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    outStream->write(bytecode.data(), bytecode.size());
}
