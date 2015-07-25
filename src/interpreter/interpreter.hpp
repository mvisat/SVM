#ifndef SVM_H
#define SVM_H

#include "../common/strutil.hpp"
#include "../common/library.hpp"
#include "../common/svm_exception.hpp"
#include "../common/typedef.hpp"

#include "../command/invoker.hpp"
#include "../command/command.hpp"
#include "../command/commandAdd.hpp"
#include "../command/commandAddImmediate.hpp"
#include "../command/commandAnd.hpp"
#include "../command/commandEqual.hpp"
#include "../command/commandGreaterThan.hpp"
#include "../command/commandHalt.hpp"
#include "../command/commandJump.hpp"
#include "../command/commandJumpAndLink.hpp"
#include "../command/commandJumpIfNotZero.hpp"
#include "../command/commandJumpIfZero.hpp"
#include "../command/commandJumpRegister.hpp"
#include "../command/commandLessThan.hpp"
#include "../command/commandLibraryCall.hpp"
#include "../command/commandLibraryLink.hpp"
#include "../command/commandLibraryOpen.hpp"
#include "../command/commandLoad.hpp"
#include "../command/commandLoadByte.hpp"
#include "../command/commandLoadImmediate.hpp"
#include "../command/commandMultiply.hpp"
#include "../command/commandNot.hpp"
#include "../command/commandOr.hpp"
#include "../command/commandStart.hpp"
#include "../command/commandStore.hpp"
#include "../command/commandStoreByte.hpp"
#include "../command/commandSubstract.hpp"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class interpreter {
public:
    interpreter();
    ~interpreter();
    void run_kei(const string& filename);
    void run_sasm(const string& filename);
    bool is_kei(const vector<opcode_t>& bytecode);
    bool is_kei(const string& filename);

private:
    void initialize();
    memory svmMemory;
    invoker cmdInvoker;
    vector<command*> cmdList;
    vector<vector<string> > syntax;
};

#endif
