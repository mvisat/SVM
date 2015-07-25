#include "commandNot.hpp"

void commandNot::execute(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc = parse_register(cmd[2]);
    execute(rDest, rSrc);
}

void commandNot::execute(const vector<opcode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    index_t rDest = cmd[pointer+1] & 0x0F;
    index_t rSrc = (cmd[pointer+1] & 0xF0) >> 4;
    execute(rDest, rSrc);
    svmMemory->set_program_counter(pointer+2);
}

void commandNot::execute(index_t rDest, index_t rSrc) {
    svmMemory->set_register(rDest, !svmMemory->get_register(rSrc));
}

void commandNot::write_bytecode(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc = parse_register(cmd[2]);
    vector<char> code;
    code.push_back(opcode());
    code.push_back((rDest & 0x0F) | ((rSrc & 0x0F) << 4));
    outStream->write(code.data(), code.size());
}
