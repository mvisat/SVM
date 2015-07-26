#include "commandJumpIfZero.hpp"

void commandJumpIfZero::execute(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    string label = cmd[2];
    execute(rDest, svmMemory->get_label(label));
}

void commandJumpIfZero::execute(const vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
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

void commandJumpIfZero::execute(index_t rDest, counter_t address) {
    if (svmMemory->get_register(rDest) == 0)
        svmMemory->set_program_counter(address);
}

void commandJumpIfZero::write_bytecode(const vector<string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    string label = cmd[2];
    vector<bytecode_t> bytecode;
    bytecode.push_back(mnemonic_code());
    bytecode.push_back(rDest & 0x0F);
    for (unsigned int i = 0; i < sizeof(counter_t); ++i)
        bytecode.push_back(0);
    outStream->write(bytecode.data(), bytecode.size());
    counter_t jumpAddress = outStream->tellp();
    (*jumpTable)[label].push_back(jumpAddress-sizeof(counter_t));
}
