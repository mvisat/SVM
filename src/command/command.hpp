#ifndef SVM_COMMAND_H
#define SVM_COMMAND_H

#include "../common/typedef.hpp"
#include "../common/parser.hpp"
#include "../common/memory.hpp"

#include <vector>
#include <iostream>

using namespace std;

/*
001 Start
002 Add
003 Add immediate
004 Substract
005 Multiply
006 And
007 Or
008 Not
009 Equal
010 Less than
011 Greater than
012 Load
013 Load byte
014 Load immediate
015 Store
016 Store byte
017 Jump if zero
018 Jump if not zero
019 Jump
020 Jump register
021 Jump and link
022 Library call
023 Halt
024 Open library
025 Link

*/

class command {
public:
    virtual ~command() {};
    virtual string name() = 0;
    virtual bytecode_t mnemonic_code() = 0;
    virtual unsigned int operand_size() = 0;
    virtual void execute(const vector<string>& cmd) = 0;
    virtual void execute(const vector<bytecode_t>& cmd) = 0;
    virtual void write_bytecode(const vector<string>& cmd) = 0;
protected:
    memory *svmMemory;
    ofstream *outStream;
    map<string, vector<counter_t> > *jumpTable;
};

#endif
