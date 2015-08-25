#include "interpreter.hpp"

interpreter::interpreter() {
    initialize();
}

interpreter::~interpreter() {
    for (unsigned int i = 0; i < cmdList.size(); ++i)
        delete cmdList[i];
}

bool interpreter::is_kei(const std::string& filename) {
    std::ifstream ifs(filename.c_str(), std::ios::binary);
    std::vector<bytecode_t> bytecode(KEI_HEADER_SIZE);
    ifs.read(bytecode.data(), KEI_HEADER_SIZE);
    return is_kei(bytecode);
}

bool interpreter::is_kei(const std::vector<bytecode_t>& bytecode) {
    if (bytecode.size() >= KEI_HEADER_SIZE) {
        return
            bytecode[0] == 0x03 &&
            bytecode[1] == 0x6b &&
            bytecode[2] == 0x65 &&
            bytecode[3] == 0x69;
    }
    return false;
}

void interpreter::run_sasm(const std::string& filename) {
    syntax = parse_file(filename);
    if (syntax.size() == 0)
        return;

    svmMemory.clear();

    for (unsigned int i = 0; i < syntax.size(); ++i)
        if (syntax[i][0][0] == '.') {
            if (svmMemory.is_label(syntax[i][0]))
                throw svm_exception("Error: Duplicate labels found");
            else
                svmMemory.set_label(syntax[i][0], i);
        }

    while (svmMemory.get_program_counter() < syntax.size() && !svmMemory.get_halt()) {
        if (syntax[svmMemory.get_program_counter()][0][0] == '.')
            svmMemory.inc_program_counter();
        else
            cmdInvoker.execute(syntax[svmMemory.get_program_counter()]);
    }

    if (!svmMemory.get_start())
        throw svm_exception("Error: Start command not found");
    if (!svmMemory.get_halt())
        throw svm_exception("Error: Halt command not found");
}

void interpreter::run_kei(const std::string& filename) {
    std::ifstream ifs(filename.c_str(), std::ios::binary | std::ios::ate);
    if (!ifs.is_open())
        throw svm_exception("Error: Failed to read file '" + filename + "'");

    std::ifstream::pos_type size = ifs.tellg();
    std::vector<bytecode_t> bytecode(size);
    ifs.seekg(0, std::ios::beg);
    ifs.read(bytecode.data(), size);
    if (!is_kei(bytecode))
        throw svm_exception("Error: Invalid kei file");

    svmMemory.clear();
    svmMemory.set_program_counter(KEI_HEADER_SIZE);
    while (svmMemory.get_program_counter() < bytecode.size() && !svmMemory.get_halt())
        cmdInvoker.execute(bytecode, svmMemory.get_program_counter());
    if (!svmMemory.get_start())
        throw svm_exception("Error: Start command not found");
    if (!svmMemory.get_halt())
        throw svm_exception("Error: Halt command not found");
}

void interpreter::initialize() {
    cmdList.push_back(new commandNoOperation(&svmMemory));
    cmdList.push_back(new commandStart(&svmMemory));
    cmdList.push_back(new commandAdd(&svmMemory));
    cmdList.push_back(new commandAddImmediate(&svmMemory));
    cmdList.push_back(new commandSubstract(&svmMemory));
    cmdList.push_back(new commandMultiply(&svmMemory));
    cmdList.push_back(new commandAnd(&svmMemory));
    cmdList.push_back(new commandOr(&svmMemory));
    cmdList.push_back(new commandNot(&svmMemory));
    cmdList.push_back(new commandEqual(&svmMemory));
    cmdList.push_back(new commandLessThan(&svmMemory));
    cmdList.push_back(new commandGreaterThan(&svmMemory));
    cmdList.push_back(new commandLoad(&svmMemory));
    cmdList.push_back(new commandLoadByte(&svmMemory));
    cmdList.push_back(new commandLoadImmediate(&svmMemory));
    cmdList.push_back(new commandStore(&svmMemory));
    cmdList.push_back(new commandStoreByte(&svmMemory));
    cmdList.push_back(new commandJumpIfZero(&svmMemory));
    cmdList.push_back(new commandJumpIfNotZero(&svmMemory));
    cmdList.push_back(new commandJump(&svmMemory));
    cmdList.push_back(new commandJumpRegister(&svmMemory));
    cmdList.push_back(new commandJumpAndLink(&svmMemory));
    cmdList.push_back(new commandLibraryCall(&svmMemory));
    cmdList.push_back(new commandHalt(&svmMemory));
    cmdList.push_back(new commandLibraryOpen(&svmMemory));
    cmdList.push_back(new commandLibraryLink(&svmMemory));

    for (unsigned int i = 0; i < cmdList.size(); ++i)
        cmdInvoker.add(cmdList[i]);
}
