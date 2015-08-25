#include "commandNot.hpp"

void commandNot::execute(const std::vector<std::string>& cmd) {
    if (svmMemory->get_start()) {
        index_t rDest = parse_register(cmd[1]);
        index_t rSrc = parse_register(cmd[2]);
        execute(rDest, rSrc);
    }
    svmMemory->inc_program_counter();
}

void commandNot::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (svmMemory->get_start()) {
        index_t rDest = cmd[pointer+1] & 0x0F;
        index_t rSrc = (cmd[pointer+1] & 0xF0) >> 4;
        execute(rDest, rSrc);
    }
    svmMemory->set_program_counter(pointer+2);
}

void commandNot::execute(index_t rDest, index_t rSrc) {
    svmMemory->set_register(rDest, !svmMemory->get_register(rSrc));
}

void commandNot::write_bytecode(const std::vector<std::string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc = parse_register(cmd[2]);
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    bytecode.push_back((rDest & 0x0F) | ((rSrc & 0x0F) << 4));
    outStream->write(bytecode.data(), bytecode.size());
}
