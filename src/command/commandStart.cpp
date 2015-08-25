#include "commandStart.hpp"

void commandStart::execute(const std::vector<std::string>& cmd) {
    execute();
}

void commandStart::execute(const std::vector<bytecode_t>& cmd) {
    execute();
}

void commandStart::execute() {
    if (svmMemory->get_start())
        throw svm_exception("Error: Start command found (already started)");
    svmMemory->set_start();
    svmMemory->inc_program_counter();
}

void commandStart::write_bytecode(const std::vector<std::string>& cmd) {
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    outStream->write(bytecode.data(), bytecode.size());
}
