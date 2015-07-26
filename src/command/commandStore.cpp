#include "commandStore.hpp"

void commandStore::execute(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc = parse_register(cmd[2]);
    address_t C = parse_constant(cmd[3]);
    execute(rDest, rSrc, C);
}

void commandStore::execute(const vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    index_t rDest = cmd[pointer+1] & 0x0F;
    index_t rSrc = (cmd[pointer+1] & 0xF0) >> 4;
    address_t C = (cmd[pointer+2] & 0xFF) | ((cmd[pointer+3] & 0xFF) << 8);
    execute(rDest, rSrc, C);
    svmMemory->set_program_counter(pointer+4);
}

void commandStore::execute(index_t rDest, index_t rSrc, address_t C) {
    svmMemory->set_memory(
        (address_t)svmMemory->get_register(rSrc) + C,
        svmMemory->get_register(rDest) & 0x00FF);
    svmMemory->set_memory(
        (address_t)svmMemory->get_register(rSrc) + C + 1,
        (svmMemory->get_register(rDest) & 0xFF00) >> 8);
}

void commandStore::write_bytecode(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc = parse_register(cmd[2]);
    address_t C = parse_constant(cmd[3]);
    vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    bytecode.push_back((rDest & 0x0F) | ((rSrc & 0x0F) << 4));
    bytecode.push_back(C & 0x00FF);
    bytecode.push_back((C & 0xFF00) >> 8);
    outStream->write(bytecode.data(), bytecode.size());
}
