#include "compiler.hpp"

using namespace std;

compiler::compiler() {
    initialize();
}

compiler::~compiler() {
    for (unsigned int i = 0; i < cmdList.size(); ++i)
        delete cmdList[i];
}

void compiler::compile(const string& source) {
    syntax = parse_file(source);

    string target = str_replace_ext(source, "kei");
    outStream.open(target.c_str(), ofstream::out | ofstream::binary);
    if (!outStream.is_open())
        throw svm_exception("Error: Failed to write file '" + target + "'");

    vector<opcode_t> kei_header;
    // magic string
    kei_header.push_back(0x03);
    kei_header.push_back(0x6b);
    kei_header.push_back(0x65);
    kei_header.push_back(0x69);
    // version
    kei_header.push_back(0x20);
    kei_header.push_back(0x4c);
    kei_header.push_back(0x6f);
    kei_header.push_back(0x76);
    kei_header.push_back(0x65);
    kei_header.push_back(0x6c);
    kei_header.push_back(0x79);
    kei_header.push_back(0x7a);
    outStream.write(kei_header.data(), kei_header.size());

    map<string, counter_t> labelTable;
    for (unsigned int i = 0; i < syntax.size(); ++i) {
        if (syntax[i][0][0] == '.')
            labelTable[syntax[i][0]] = outStream.tellp();
        else
            cmdInvoker.write_bytecode(syntax[i]);
    }

    for (map<string, vector<counter_t> >::iterator it = jumpTable.begin(); it != jumpTable.end(); ++it) {
        vector<opcode_t> jumpBuf;
        counter_t jump = labelTable[it->first];
        for (unsigned int j = 0; j < sizeof(counter_t); ++j) {
            jumpBuf.push_back(jump & 0xFF);
            jump >>= 8;
        }
        vector<counter_t> v = it->second;
        for (unsigned int i = 0; i < v.size(); ++i) {
            outStream.seekp(v[i], ios::beg);
            outStream.write(jumpBuf.data(), jumpBuf.size());
        }
    }
    outStream.close();
    jumpTable.clear();
}

void compiler::initialize() {
    cmdList.push_back(new commandStart(&outStream));
    cmdList.push_back(new commandAdd(&outStream));
    cmdList.push_back(new commandAddImmediate(&outStream));
    cmdList.push_back(new commandSubstract(&outStream));
    cmdList.push_back(new commandMultiply(&outStream));
    cmdList.push_back(new commandAnd(&outStream));
    cmdList.push_back(new commandOr(&outStream));
    cmdList.push_back(new commandNot(&outStream));
    cmdList.push_back(new commandEqual(&outStream));
    cmdList.push_back(new commandLessThan(&outStream));
    cmdList.push_back(new commandGreaterThan(&outStream));
    cmdList.push_back(new commandLoad(&outStream));
    cmdList.push_back(new commandLoadByte(&outStream));
    cmdList.push_back(new commandLoadImmediate(&outStream));
    cmdList.push_back(new commandStore(&outStream));
    cmdList.push_back(new commandStoreByte(&outStream));
    cmdList.push_back(new commandJumpIfZero(&outStream, &jumpTable));
    cmdList.push_back(new commandJumpIfNotZero(&outStream, &jumpTable));
    cmdList.push_back(new commandJump(&outStream, &jumpTable));
    cmdList.push_back(new commandJumpRegister(&outStream, &jumpTable));
    cmdList.push_back(new commandJumpAndLink(&outStream, &jumpTable));
    cmdList.push_back(new commandLibraryCall(&outStream));
    cmdList.push_back(new commandHalt(&outStream));
    cmdList.push_back(new commandLibraryOpen(&outStream));
    cmdList.push_back(new commandLibraryLink(&outStream));

    for (unsigned int i = 0; i < cmdList.size(); ++i)
        cmdInvoker.add(cmdList[i]);
}
