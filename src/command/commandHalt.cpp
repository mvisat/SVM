#include "commandHalt.hpp"

void commandHalt::execute(const vector<string>& cmd) {
    execute();
}

void commandHalt::execute(const vector<opcode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    execute();
    svmMemory->set_program_counter(pointer+1);
}

void commandHalt::execute() {
    svmMemory->set_halt(true);
}

void commandHalt::write_bytecode(const vector<string>& cmd) {
    vector<char> code;
    code.push_back(opcode());
    outStream->write(code.data(), code.size());
}
