#include "commandLoad.hpp"

void commandLoad::execute(const std::vector<std::string>& cmd) {
    if (svmMemory->get_start()) {
        index_t rDest = parse_register(cmd[1]);
        index_t rSrc = parse_register(cmd[2]);
        address_t C = parse_constant(cmd[3]);
        execute(rDest, rSrc, C);
    }
    svmMemory->inc_program_counter();
}

void commandLoad::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (svmMemory->get_start()) {
        index_t rDest = cmd[pointer+1] & 0x0F;
        index_t rSrc = (cmd[pointer+1] & 0xF0) >> 4;
        address_t C = (cmd[pointer+2] & 0xFF) | ((cmd[pointer+3] & 0xFF) << 8);
        execute(rDest, rSrc, C);
    }
    svmMemory->set_program_counter(pointer+4);
}

void commandLoad::execute(index_t rDest, index_t rSrc, address_t C) {
    svmMemory->set_register(rDest,
        ((svmMemory->get_memory((address_t)svmMemory->get_register(rSrc) + C)) & 0xFF) |
        ((svmMemory->get_memory((address_t)svmMemory->get_register(rSrc) + C + 1) & 0xFF) << 8));
}

void commandLoad::write_bytecode(const std::vector<std::string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc = parse_register(cmd[2]);
    address_t C = parse_constant(cmd[3]);
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    bytecode.push_back((rDest & 0x0F) | ((rSrc & 0x0F) << 4));
    bytecode.push_back(C & 0x00FF);
    bytecode.push_back((C & 0xFF00) >> 8);
    outStream->write(bytecode.data(), bytecode.size());
}
