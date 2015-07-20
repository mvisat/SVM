#include "memory.hpp"

const int memory::MAX_REGISTER = 16;
const int memory::MAX_MEMORY = 65536;

memory::memory() {
    Register.resize(MAX_REGISTER);
    Memory.resize(MAX_MEMORY);
    clear();
}

memory::~memory() {
    for (map<string, lib_t>::iterator it = LibHandle.begin(); it != LibHandle.end(); ++it)
        LibUnload(it->second);
}

void memory::clear() {
    ProgramCounter = 0;
    for (int i = 0; i < MAX_REGISTER; ++i)
        Register[i] = 0;
    for (int i = 0; i < MAX_MEMORY; ++i)
        Memory[i] = 0;
    Label.clear();
}

bool memory::getHalt() {
    return Halt;
}

void memory::setHalt(bool value) {
    Halt = value;
}

register_t memory::getRegister(int regIndex) {
    return Register[regIndex];
}

void memory::setRegister(int regIndex, register_t value) {
    Register[regIndex] = value;
}

memory_t memory::getMemory(address_t address) {
    return Memory[address];
}

memory_t* memory::getMemoryData() {
    return Memory.data();
}

void memory::setMemory(address_t address, memory_t value) {
    Memory[address] = value;
}

int memory::getProgramCounter() {
    return ProgramCounter;
}

void memory::setProgramCounter(int value) {
    ProgramCounter = value;
}

int memory::getLabel(const string& labelName) {
    return Label[labelName];
}

void memory::setLabel(const string& labelName, int value) {
    Label[labelName] = value;
}

FuncPrototype memory::getLibFunction(const string& functionName) {
    if (LibFunction.find(functionName) != LibFunction.end())
        return LibFunction[functionName];
    else
        return 0;
}

void memory::linkLibFunction(const string& functionName) {
    if (LastHandle) {
        FuncPrototype f = 0;
        if (f = (FuncPrototype)::LoadProc(LastHandle, functionName.substr(1).c_str()))
            LibFunction[functionName] = f;
        else
            throw svm_exception("Error: Failed to link function '" + functionName + "'");
    }
}

void memory::loadLib(const string& libName) {
    if (LibHandle.find(libName) == LibHandle.end()) {
        lib_t handle = 0;
        #ifdef _WIN32
            handle = LibLoad(libName.c_str());
        #else
            if (libName.size() && (libName[0] == '.' || libName[0] == '/'))
                handle = LibLoad(libName.c_str());
            else
                handle = LibLoad(("./" + libName).c_str());
        #endif
        if (handle) {
            LibHandle[libName] = handle;
            LastHandle = handle;
        }
        else {
            throw svm_exception("Error: Failed to load library '" + libName + "'");
        }
    }
}


