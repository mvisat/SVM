#include "commandNoOperation.hpp"

void commandNoOperation::execute(const vector<string>& cmd) {

};

void commandNoOperation::execute(const vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    svmMemory->set_program_counter(pointer+1);
}

void commandNoOperation::execute() {
}

void commandNoOperation::write_bytecode(const vector<string>& cmd) {
    vector<bytecode_t> bytecode;
    bytecode.push_back(mnemonic_code());
    outStream->write(bytecode.data(), bytecode.size());
}
