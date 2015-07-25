#include "commandStart.hpp"

void commandStart::execute(const vector<string>& cmd) {
}

void commandStart::execute(const vector<opcode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    execute();
    svmMemory->set_program_counter(pointer+1);
}

void commandStart::execute() {
}

void commandStart::write_bytecode(const vector<string>& cmd) {
    vector<char> code;
    code.push_back(opcode());
    outStream->write(code.data(), code.size());
}
