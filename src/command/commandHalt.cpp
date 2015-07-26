#include "commandHalt.hpp"

void commandHalt::execute(const vector<string>& cmd) {
    execute();
}

void commandHalt::execute(const vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    execute();
    svmMemory->set_program_counter(pointer+1);
}

void commandHalt::execute() {
    svmMemory->set_halt(true);
}

void commandHalt::write_bytecode(const vector<string>& cmd) {
    vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    outStream->write(bytecode.data(), bytecode.size());
}
