#include "commandJumpRegister.hpp"

void commandJumpRegister::execute(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    execute(rDest);
}

void commandJumpRegister::execute(const vector<opcode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    index_t rDest = cmd[pointer+1] & 0x0F;
    execute(rDest);
}

void commandJumpRegister::execute(index_t rDest) {
    svmMemory->set_program_counter(svmMemory->get_register(rDest));
}

void commandJumpRegister::write_bytecode(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    vector<char> code;
    code.push_back(opcode());
    code.push_back(rDest & 0x0F);
    outStream->write(code.data(), code.size());
}
