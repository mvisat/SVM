#include "commandNoOperation.hpp"

void commandNoOperation::execute(const std::vector<std::string>& cmd) {
    svmMemory->inc_program_counter();
};

void commandNoOperation::execute(const std::vector<bytecode_t>& cmd) {
    svmMemory->inc_program_counter();
}

void commandNoOperation::execute() {
}

void commandNoOperation::write_bytecode(const std::vector<std::string>& cmd) {
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    outStream->write(bytecode.data(), bytecode.size());
}
