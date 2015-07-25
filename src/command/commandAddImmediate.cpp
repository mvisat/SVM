#include "commandAddImmediate.hpp"

void commandAddImmediate::execute(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc = parse_register(cmd[2]);
    register_t C = parse_constant(cmd[3]);
    execute(rDest, rSrc, C);
}

void commandAddImmediate::execute(const vector<opcode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    index_t rDest = cmd[pointer+1] & 0x0F;
    index_t rSrc = (cmd[pointer+1] & 0xF0) >> 4;
    register_t C = (cmd[pointer+2] & 0xFF) | ((cmd[pointer+3] & 0xFF) << 8);
    execute(rDest, rSrc, C);
    svmMemory->set_program_counter(pointer+4);
}

void commandAddImmediate::execute(index_t rDest, index_t rSrc, register_t C) {
    svmMemory->set_register(rDest, svmMemory->get_register(rSrc) + C);
}

void commandAddImmediate::write_bytecode(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc = parse_register(cmd[2]);
    register_t C = parse_constant(cmd[3]);
    vector<char> code;
    code.push_back(opcode());
    code.push_back((rDest & 0x0F) | ((rSrc & 0x0F) << 4));
    code.push_back(C & 0x00FF);
    code.push_back((C & 0xFF00) >> 8);
    outStream->write(code.data(), code.size());
}
