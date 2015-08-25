#include "commandJumpAndLink.hpp"

void commandJumpAndLink::execute(const std::vector<std::string>& cmd) {
    if (svmMemory->get_start()) {
        index_t rDest = parse_register(cmd[1]);
        std::string label = cmd[2];
        execute(rDest, svmMemory->get_label(label));
    }
    svmMemory->inc_program_counter();
}

void commandJumpAndLink::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (svmMemory->get_start()) {
        index_t rDest = cmd[pointer+1] & 0x0F;
        pointer = pointer + 2;
        counter_t address = 0;
        for (unsigned int i = 0; i < sizeof(counter_t); ++i) {
            address = address | ((cmd[pointer] & 0xFF) << (i << 3));
            ++pointer;
        }
        svmMemory->set_program_counter(pointer);
        execute(rDest, address);
    }
    else
        svmMemory->set_program_counter(pointer+sizeof(counter_t)+2);
}

void commandJumpAndLink::execute(index_t rDest, counter_t address) {
    svmMemory->set_register(rDest, svmMemory->get_program_counter());
    svmMemory->set_program_counter(address);
}

void commandJumpAndLink::write_bytecode(const std::vector<std::string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    std::string label = cmd[2];
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    bytecode.push_back(rDest & 0x0F);
    for (unsigned int i = 0; i < sizeof(counter_t); ++i)
        bytecode.push_back(0);
    outStream->write(bytecode.data(), bytecode.size());
    counter_t jumpAddress = outStream->tellp();
    (*jumpTable)[label].push_back(jumpAddress-sizeof(counter_t));
}
