#ifndef COMPILER_H
#define COMPILER_H

#include "../common/parser.hpp"
#include "../common/memory.hpp"

#include "../command/invoker.hpp"
#include "../command/command.hpp"
#include "../command/commandStart.hpp"
#include "../command/commandAdd.hpp"
#include "../command/commandAddImmediate.hpp"
#include "../command/commandSubstract.hpp"
#include "../command/commandMultiply.hpp"
#include "../command/commandAnd.hpp"
#include "../command/commandOr.hpp"
#include "../command/commandNot.hpp"
#include "../command/commandEqual.hpp"
#include "../command/commandLessThan.hpp"
#include "../command/commandGreaterThan.hpp"
#include "../command/commandLoad.hpp"
#include "../command/commandLoadByte.hpp"
#include "../command/commandLoadImmediate.hpp"
#include "../command/commandStore.hpp"
#include "../command/commandStoreByte.hpp"
#include "../command/commandJumpIfZero.hpp"
#include "../command/commandJumpIfNotZero.hpp"
#include "../command/commandJump.hpp"
#include "../command/commandJumpRegister.hpp"
#include "../command/commandJumpAndLink.hpp"
#include "../command/commandLibraryCall.hpp"
#include "../command/commandHalt.hpp"
#include "../command/commandLibraryLink.hpp"
#include "../command/commandLibraryOpen.hpp"

#include <map>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class compiler {
public:
    compiler();
    ~compiler();
    void compile(const string& source);
private:
    vector<vector<string> > syntax;
    vector<command*> cmdList;
    invoker cmdInvoker;
    ofstream outStream;
    map<string, vector<counter_t> > jumpTable;
    void initialize();
};

#endif
