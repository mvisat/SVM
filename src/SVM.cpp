#include "svm.hpp"

svm::svm(const string& fileName /* = "" */ ) {
    initialize();
    if (fileName.size() > 0)
        load(fileName);
}

svm::~svm() {
    for (int i = 0; i < cmdList.size(); ++i)
        delete cmdList[i];
}

void svm::load(const string& fileName) {
    syntax.clear();
    ifstream input(fileName.c_str());
    if (input.is_open()) {
        string s;
        while (getline(input, s)) {
            vector<string> v = strSplitByWhitespace(s);
            for (int i = 0; i < v.size(); ++i) {
                if (v[i] == "#") {
                    while (i < v.size())
                        v.erase(v.begin()+i);
                    break;
                }
            }
            if (v.size())
                syntax.push_back(v);
        }

        #ifdef DEBUG
            for (int i = 0; i < syntax.size(); ++i) {
                for (int j = 0; j < syntax[i].size(); ++j)
                    cout << syntax[i][j] << " ";
                cout << endl;
            }
        #endif
    }
    else {
        throw svm_exception("Error: Failed to read file '" + fileName + "'");
    }
}

void svm::run() {
    if (syntax.size() == 0)
        return;

    svmMemory.clear();
    for (int i = 0; i < syntax.size(); ++i) {
        if (syntax[i][0][0] == '.')
            svmMemory.setLabel(syntax[i][0], i);
    }
    while (svmMemory.getProgramCounter() < syntax.size() && !svmMemory.getHalt()) {
        #ifdef DEBUG
            cout << "Run:: " << svmMemory.getProgramCounter() << " ";
            for (int i = 0; i < syntax[svmMemory.getProgramCounter()].size(); ++i)
                cout << syntax[svmMemory.getProgramCounter()][i] << " ";
            cout << endl;
        #endif

        cmdInvoker.execute(syntax[svmMemory.getProgramCounter()]);
        svmMemory.setProgramCounter(svmMemory.getProgramCounter()+1);

        #ifdef DEBUG
            for (int i = 0; i < memory::MAX_REGISTER; ++i)
                cout << "$" << i << " = " << svmMemory.getRegister(i) << endl;
            for (int i = 0; i < 10; ++i)
                cout << (int)svmMemory.getMemory(i) << " ";
            cout << endl;
            for (int i = memory::MAX_MEMORY-10; i < memory::MAX_MEMORY; ++i)
                cout << (int)svmMemory.getMemory(i) << " ";
            cout << endl;
        #endif
    }
}

void svm::initialize() {
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

    for (int i = 0; i < cmdList.size(); ++i)
        cmdInvoker.add(cmdList[i]);
}
