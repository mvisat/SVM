#include "compiler.hpp"

compiler::compiler() {
    initialize();
}

compiler::~compiler() {
    for (unsigned int i = 0; i < cmdList.size(); ++i)
        delete cmdList[i];
}

void compiler::compile(const std::string& source) {
    syntax = parse_file(source);

    std::string target;
    if (str_find_ext(source) == "sasm")
        target = str_replace_ext(source, "kei");
    else
        target = source + ".kei";
    outStream.open(target.c_str(), std::ofstream::out | std::ofstream::binary);
    if (!outStream.is_open())
        throw svm_exception("Error: Failed to write file '" + target + "'");

    std::vector<bytecode_t> kei_header;
    // magic std::string
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

    std::map<std::string, counter_t> labelTable;
    for (unsigned int i = 0; i < syntax.size(); ++i) {
        std::string cur = syntax[i][0];
        if (cur[0] == '.') {
            if (labelTable.find(cur) == labelTable.end())
                labelTable[cur] = outStream.tellp();
            else
                throw svm_exception("Error: Duplicate labels found");
        }
        else
            cmdInvoker.write_bytecode(syntax[i]);
    }

    for (std::map<std::string, std::vector<counter_t> >::iterator it = jumpTable.begin(); it != jumpTable.end(); ++it) {
        std::vector<bytecode_t> jumpBuf;
        std::map<std::string, counter_t>::iterator it_label = labelTable.find(it->first);
        if (it_label == labelTable.end())
            throw svm_exception("Error: Label '" + it->first + "' not found");
        counter_t jump = it_label->second;
        for (unsigned int j = 0; j < sizeof(counter_t); ++j) {
            jumpBuf.push_back(jump & 0xFF);
            jump >>= 8;
        }
        std::vector<counter_t> v = it->second;
        for (unsigned int i = 0; i < v.size(); ++i) {
            outStream.seekp(v[i], std::ios::beg);
            outStream.write(jumpBuf.data(), jumpBuf.size());
        }
    }
    outStream.close();
    jumpTable.clear();
}

void compiler::initialize() {
    cmdList.push_back(new commandNoOperation(&outStream));
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
