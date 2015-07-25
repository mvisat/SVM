#include "commandJump.hpp"

void commandJump::execute(const vector<string>& cmd) {
    string label = cmd[1];
    execute(svmMemory->get_label(label));
}

void commandJump::execute(const vector<opcode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    pointer = pointer + 1;
    counter_t address = 0;
    for (unsigned int i = 0; i < sizeof(counter_t); ++i) {
        address = address | (cmd[pointer+i] << (i << 3));
    }
    execute(address);
}

void commandJump::execute(counter_t address) {
    svmMemory->set_program_counter(address);
}

void commandJump::write_bytecode(const vector<string>& cmd) {
    string label = cmd[1];
    vector<char> code;
    code.push_back(opcode());
    for (unsigned int i = 0; i < sizeof(counter_t); ++i)
        code.push_back(0);
    outStream->write(code.data(), code.size());
    counter_t jumpAddress = outStream->tellp();
    (*jumpTable)[label].push_back(jumpAddress-sizeof(counter_t));
}
