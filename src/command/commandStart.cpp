#include "commandStart.hpp"

void commandStart::execute(const vector<string>& cmd) {
}

void commandStart::execute(const vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    execute();
    svmMemory->set_program_counter(pointer+1);
}

void commandStart::execute() {
}

void commandStart::write_bytecode(const vector<string>& cmd) {
    vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    outStream->write(bytecode.data(), bytecode.size());
}
