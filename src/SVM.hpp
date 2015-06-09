#ifndef SVM_H
#define SVM_H

#include "StrUtil.hpp"
#include "LibCall.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

typedef void (*FuncPrototype)(int* target, int src, char* memory);

class SVM
{
public:
    SVM();
    SVM(const string& FileName);
    ~SVM();
    void Load(const string& FileName);
    void Run();

private:
    bool Halt;
    int ProgramCounter;
    vector<vector<string> > Syntax;
    vector<int> Register;
    vector<char> Memory;
    map<string, int> Label;
    static const int MaxRegister;
    static const int MaxMemory;
    map<string, lib_t> LibHandle;
    lib_t LastHandle;
    map<string, FuncPrototype> LibFunction;

    void Initialize();

    int ParseRegister(const string& s);
    void Process(const vector<string>& cmd);

    void CmdAdd(int rDest, int rSrc1, int rSrc2);
    void CmdAddImmediate(int rDest, int rSrc, int C);
    void CmdSubstract(int rDest, int rSrc1, int rSrc2);
    void CmdMultiply(int rDest, int rSrc1, int rSrc2);
    void CmdAnd(int rDest, int rSrc1, int rSrc2);
    void CmdOr(int rDest, int rSrc1, int rSrc2);
    void CmdNot(int rDest, int rSrc);
    void CmdEqual(int rDest, int rSrc1, int rSrc2);
    void CmdLessThan(int rDest, int rSrc1, int rSrc2);
    void CmdGreaterThan(int rDest, int rSrc1, int rSrc2);
    void CmdLoad(int rDest, int rSrc, int C);
    void CmdLoadByte(int rDest, int rSrc, int C);
    void CmdLoadImmediate(int rDest, int C);
    void CmdStore(int rDest, int rSrc, int C);
    void CmdStoreByte(int rDest, int rSrc, int C);
    void CmdJumpIfZero(int rDest, const string& label);
    void CmdJumpIfNotZero(int rDest, const string& label);
    void CmdJump(const string& label);
    void CmdJumpRegister(int rDest);
    void CmdJumpAndLink(int rDest, const string& label);
    void CmdLibraryCall(int rDest, int rSrc, const string& func);
    void CmdLibraryOpen(const string& lib);
    void CmdLibraryLink(const string& func);
};

#endif
