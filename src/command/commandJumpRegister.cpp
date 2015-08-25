#include "commandJumpRegister.hpp"

void commandJumpRegister::execute(const std::vector<std::string>& cmd) {
    if (svmMemory->get_start()) {
        index_t rDest = parse_register(cmd[1]);
        execute(rDest);
    }
    svmMemory->inc_program_counter();
}

void commandJumpRegister::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (svmMemory->get_start()) {
        index_t rDest = cmd[pointer+1] & 0x0F;
        execute(rDest);
    }
    else
        svmMemory->set_program_counter(pointer+2);
}

void commandJumpRegister::execute(index_t rDest) {
    svmMemory->set_program_counter(svmMemory->get_register(rDest));
}

void commandJumpRegister::write_bytecode(const std::vector<std::string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    bytecode.push_back(rDest & 0x0F);
    outStream->write(bytecode.data(), bytecode.size());
}
