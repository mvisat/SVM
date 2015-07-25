#include "memory.hpp"

const int memory::MAX_REGISTER = 16;
const int memory::MAX_MEMORY = 65536;

memory::memory(): Register(MAX_REGISTER), Memory(MAX_MEMORY), LastHandle(0) {
    clear();
}

memory::~memory() {
    for (map<string, lib_t>::iterator it = LibHandle.begin(); it != LibHandle.end(); ++it)
        LibUnload(it->second);
}

void memory::clear() {
    Halt = false;
    ProgramCounter = 0;
    for (unsigned int i = 0; i < MAX_REGISTER; ++i)
        Register[i] = 0;
    for (unsigned int i = 0; i < MAX_MEMORY; ++i)
        Memory[i] = 0;
    Label.clear();
}

counter_t memory::get_label(const string& label_name) {
    map<string, counter_t>::iterator it = Label.find(label_name);
    if (it != Label.end())
        return it->second;
    else
        return 0;
}

void memory::set_label(const string& label_name, counter_t value) {
    Label[label_name] = value;
}

function_t memory::get_lib_function(const string& function_name) {
    map<string, function_t>::iterator it = LibFunction.find(function_name);
    if (it != LibFunction.end())
        return it->second;
    else
        return 0;
}

void memory::link_lib_function(const string& function_name) {
    if (LastHandle) {
        function_t f = (function_t)::LoadProc(LastHandle, function_name.substr(1).c_str());
        if (f)
            LibFunction[function_name] = f;
        else
            throw svm_exception("Error: Failed to link function '" + function_name + "'");
    }
}

void memory::load_lib(const string& lib_name) {
    if (LibHandle.find(lib_name) == LibHandle.end()) {
        lib_t handle = 0;
        #ifdef _WIN32
            handle = LibLoad(lib_name.c_str());
        #else
            if (lib_name.size() && (lib_name[0] == '.' || lib_name[0] == '/'))
                handle = LibLoad(lib_name.c_str());
            else
                handle = LibLoad(("./" + lib_name).c_str());
        #endif
        if (handle) {
            LibHandle[lib_name] = handle;
            LastHandle = handle;
        }
        else {
            throw svm_exception("Error: Failed to load library '" + lib_name + "'");
        }
    }
}


