#include "commandSubstract.hpp"

void commandSubstract::execute(const std::vector<std::string>& cmd) {
    if (svmMemory->get_start()) {
        index_t rDest = parse_register(cmd[1]);
        index_t rSrc1 = parse_register(cmd[2]);
        index_t rSrc2 = parse_register(cmd[3]);
        execute(rDest, rSrc1, rSrc2);
    }
    svmMemory->inc_program_counter();
}

void commandSubstract::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (svmMemory->get_start()) {
        index_t rDest = cmd[pointer+1] & 0x0F;
        index_t rSrc1 = (cmd[pointer+1] & 0xF0) >> 4;
        index_t rSrc2 = cmd[pointer+2] & 0x0F;
        execute(rDest, rSrc1, rSrc2);
    }
    svmMemory->set_program_counter(pointer+3);
}

void commandSubstract::execute(index_t rDest, index_t rSrc1, index_t rSrc2) {
    svmMemory->set_register(
        rDest,
        svmMemory->get_register(rSrc1) - svmMemory->get_register(rSrc2));
}

void commandSubstract::write_bytecode(const std::vector<std::string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc1 = parse_register(cmd[2]);
    index_t rSrc2 = parse_register(cmd[3]);
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    bytecode.push_back((rDest & 0x0F) | ((rSrc1 & 0x0F) << 4));
    bytecode.push_back(rSrc2 & 0x0F);
    outStream->write(bytecode.data(), bytecode.size());
}
