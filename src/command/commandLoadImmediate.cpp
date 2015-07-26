#include "commandLoadImmediate.hpp"

void commandLoadImmediate::execute(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    register_t C = parse_constant(cmd[2]);
    execute(rDest, C);
}

void commandLoadImmediate::execute(const vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    index_t rDest = cmd[pointer+1] & 0x0F;
    register_t C = (cmd[pointer+2] & 0xFF) | ((cmd[pointer+3] & 0xFF) << 8);
    execute(rDest, C);
    svmMemory->set_program_counter(pointer+4);
}

void commandLoadImmediate::execute(index_t rDest, register_t C) {
    svmMemory->set_register(rDest, C);
}

void commandLoadImmediate::write_bytecode(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    register_t C = parse_constant(cmd[2]);
    vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    bytecode.push_back((rDest & 0x0F));
    bytecode.push_back(C & 0x00FF);
    bytecode.push_back((C & 0xFF00) >> 8);
    outStream->write(bytecode.data(), bytecode.size());
}
