#ifndef MEMORY_H
#define MEMORY_H

#include "typedef.hpp"
#include "library.hpp"
#include "svm_exception.hpp"

#include <map>
#include <vector>
#include <string>

using namespace std;

typedef void (*FuncPrototype)(int* target, int src, char* memory);

class memory {
public:
    memory();
    ~memory();

    static const int MAX_REGISTER;
    static const int MAX_MEMORY;

    void clear();

    bool getHalt();
    void setHalt(bool value);

    int getProgramCounter();
    void setProgramCounter(int value);

    register_t getRegister(int regIndex);
    void setRegister(int regIndex, register_t value);

    memory_t getMemory(address_t address);
    memory_t* getMemoryData();
    void setMemory(address_t address, memory_t value);

    int getLabel(const string& labelName);
    void setLabel(const string& labelName, int value);
    void clearLabel();

    FuncPrototype getLibFunction(const string& functionName);
    void linkLibFunction(const string& functionName);
    void loadLib(const string& libName);

private:

    bool Halt;
    int ProgramCounter;
    vector<register_t> Register;
    vector<memory_t> Memory;
    map<string, int> Label;

    map<string, lib_t> LibHandle;
    lib_t LastHandle;
    map<string, FuncPrototype> LibFunction;
};


#endif
