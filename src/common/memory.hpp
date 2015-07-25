#ifndef MEMORY_H
#define MEMORY_H

#include "typedef.hpp"
#include "library.hpp"
#include "svm_exception.hpp"

#include <map>
#include <vector>
#include <string>

using namespace std;

typedef void (*function_t)(int* target, int src, char* memory);

class memory {
public:
    memory();
    ~memory();

    static const int MAX_REGISTER;
    static const int MAX_MEMORY;

    void clear();

    bool get_halt() { return Halt; };
    void set_halt(bool value) { Halt = value; };

    counter_t get_program_counter() { return ProgramCounter; };
    void set_program_counter(counter_t value) { ProgramCounter = value; }

    register_t get_register(index_t register_index) { return Register[register_index]; };
    void set_register(index_t register_index, register_t value) { Register[register_index] = value; };

    memory_t get_memory(address_t address) { return Memory[address]; };
    memory_t* get_memory_data() { return Memory.data(); };
    void set_memory(address_t address, memory_t value) { Memory[address] = value; };

    counter_t get_label(const string& label_name);
    void set_label(const string& label_name, counter_t value);

    function_t get_lib_function(const string& function_name);
    void link_lib_function(const string& function_name);
    void load_lib(const string& lib_name);

private:
    bool Halt;
    counter_t ProgramCounter;
    vector<register_t> Register;
    vector<memory_t> Memory;
    map<string, counter_t> Label;

    map<string, lib_t> LibHandle;
    lib_t LastHandle;
    map<string, function_t> LibFunction;
};


#endif
