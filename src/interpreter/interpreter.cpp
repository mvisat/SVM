#include "interpreter.hpp"

interpreter::interpreter() {
    initialize();
}

interpreter::~interpreter() {
    for (unsigned int i = 0; i < cmdList.size(); ++i)
        delete cmdList[i];
}

bool interpreter::is_kei(const string& filename) {
    ifstream ifs(filename.c_str(), ios::binary);
    vector<bytecode_t> bytecode(KEI_HEADER_SIZE);
    ifs.read(bytecode.data(), KEI_HEADER_SIZE);
    return is_kei(bytecode);
}

bool interpreter::is_kei(const vector<bytecode_t>& bytecode) {
    if (bytecode.size() >= KEI_HEADER_SIZE) {
        return
            bytecode[0] == 0x03 &&
            bytecode[1] == 0x6b &&
            bytecode[2] == 0x65 &&
            bytecode[3] == 0x69;
    }
    return false;
}

void interpreter::run_sasm(const string& filename) {
    syntax = parse_file(filename);
    if (syntax.size() == 0)
        return;

    svmMemory.clear();
    for (unsigned int i = 0; i < syntax.size(); ++i) {
        if (syntax[i][0][0] == '.')
            svmMemory.set_label(syntax[i][0], i);
    }
    while (svmMemory.get_program_counter() < syntax.size() && !svmMemory.get_halt()) {
        #ifdef DEBUG
            cout << "Run:: " << svmMemory.get_program_counter() << " ";
            for (unsigned int i = 0; i < syntax[svmMemory.get_program_counter()].size(); ++i)
                cout << syntax[svmMemory.get_program_counter()][i] << " ";
            cout << endl;
        #endif

        cmdInvoker.execute(syntax[svmMemory.get_program_counter()]);
        svmMemory.set_program_counter(svmMemory.get_program_counter()+1);

        #ifdef DEBUG
            for (unsigned int i = 0; i < memory::MAX_REGISTER; ++i)
                cout << "$" << i << " = " << svmMemory.get_register(i) << endl;
            for (unsigned int i = 0; i < 10; ++i)
                cout << (int)svmMemory.get_memory(i) << " ";
            cout << endl;
            for (unsigned int i = memory::MAX_MEMORY-10; i < memory::MAX_MEMORY; ++i)
                cout << (int)svmMemory.get_memory(i) << " ";
            cout << endl;
        #endif
    }
}

void interpreter::run_kei(const string& filename) {
    ifstream ifs(filename.c_str(), ios::binary | ios::ate);
    if (!ifs.is_open())
        throw svm_exception("Error: Failed to read file '" + filename + "'");

    ifstream::pos_type size = ifs.tellg();
    vector<bytecode_t> bytecode(size);
    ifs.seekg(0, ios::beg);
    ifs.read(bytecode.data(), size);
    if (!is_kei(bytecode))
        throw svm_exception("Error: Invalid kei file");

    svmMemory.clear();
    svmMemory.set_program_counter(KEI_HEADER_SIZE);
    while (svmMemory.get_program_counter() < bytecode.size() && !svmMemory.get_halt()) {
        cmdInvoker.execute(bytecode, svmMemory.get_program_counter());
    }
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
