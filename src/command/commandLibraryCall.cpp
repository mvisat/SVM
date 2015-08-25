#include "commandLibraryCall.hpp"

void commandLibraryCall::execute(const std::vector<std::string>& cmd) {
    if (svmMemory->get_start()) {
        index_t rDest = parse_register(cmd[1]);
        index_t rSrc = parse_register(cmd[2]);
        std::string func = parse_function(cmd[3]);
        execute(rDest, rSrc, func);
    }
    svmMemory->inc_program_counter();
}

void commandLibraryCall::execute(const std::vector<bytecode_t>& cmd) {
    counter_t pointer = svmMemory->get_program_counter();
    if (svmMemory->get_start()) {
        index_t rDest = cmd[pointer+1] & 0x0F;
        index_t rSrc = (cmd[pointer+1] & 0xF0) >> 4;
        std::string func;
        pointer = pointer + 2;
        while (cmd[pointer] != 0)
            func += cmd[pointer++];
        execute(rDest, rSrc, parse_function(func));
    }
    else {
        ++pointer;
        while (cmd[++pointer] != 0);
    }
    svmMemory->set_program_counter(pointer+1);
}

void commandLibraryCall::execute(index_t rDest, index_t rSrc, const std::string& func) {
    if (func == "input") {
        int in;
        std::cin >> in;
        svmMemory->set_register(rDest, (register_t)in);
    }
    else if (func == "output") {
        std::cout << svmMemory->get_register(rSrc) << std::endl;
    }
    else {
        function_t f = svmMemory->get_lib_function(func);
        if (f) {
            int registerDummyDest = svmMemory->get_register(rDest);
            int registerDummySrc = svmMemory->get_register(rSrc);
            f(&registerDummyDest, registerDummySrc, (char*)svmMemory->get_memory_data());
            svmMemory->set_register(rDest, (register_t)registerDummyDest);
        }
    }
}

void commandLibraryCall::write_bytecode(const std::vector<std::string>& cmd) {
    index_t rDest = parse_register(cmd[1]);
    index_t rSrc = parse_register(cmd[2]);
    std::string func = cmd[3];
    std::vector<bytecode_t> bytecode;
    bytecode.push_back(static_cast<bytecode_t>(mnemonic_code()));
    bytecode.push_back((rDest & 0x0F) | ((rSrc & 0x0F) << 4));
    for (unsigned int i = 0; i < func.size(); ++i)
        bytecode.push_back(func[i]);
    bytecode.push_back(0x00);
    outStream->write(bytecode.data(), bytecode.size());
}
