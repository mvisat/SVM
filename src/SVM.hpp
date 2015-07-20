#ifndef SVM_H
#define SVM_H

#include "strutil.hpp"
#include "library.hpp"
#include "svm_exception.hpp"
#include "typedef.hpp"

#include "invoker.hpp"
#include "command/command.hpp"
#include "command/commandAdd.hpp"
#include "command/commandAddImmediate.hpp"
#include "command/commandAnd.hpp"
#include "command/commandEqual.hpp"
#include "command/commandGreaterThan.hpp"
#include "command/commandHalt.hpp"
#include "command/commandJump.hpp"
#include "command/commandJumpAndLink.hpp"
#include "command/commandJumpIfNotZero.hpp"
#include "command/commandJumpIfZero.hpp"
#include "command/commandJumpRegister.hpp"
#include "command/commandLessThan.hpp"
#include "command/commandLibraryCall.hpp"
#include "command/commandLibraryLink.hpp"
#include "command/commandLibraryOpen.hpp"
#include "command/commandLoad.hpp"
#include "command/commandLoadByte.hpp"
#include "command/commandLoadImmediate.hpp"
#include "command/commandMultiply.hpp"
#include "command/commandNot.hpp"
#include "command/commandOr.hpp"
#include "command/commandStart.hpp"
#include "command/commandStore.hpp"
#include "command/commandStoreByte.hpp"
#include "command/commandSubstract.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class svm {
public:
    svm(const string& FileName = "");
    ~svm();
    void load(const string& FileName);
    void run();

private:
    void initialize();
    memory svmMemory;
    invoker cmdInvoker;
    vector<command*> cmdList;
    vector<vector<string> > syntax;
};

#endif
