#ifndef COMMON_MEMORY_H
#define COMMON_MEMORY_H

#include "typedef.hpp"
#include "library.hpp"
#include "svm_exception.hpp"

#include <map>
#include <vector>
#include <string>

typedef void (*function_t)(int* target, int src, char* memory);

class memory {
public:
    memory();
    ~memory();

    static const int MAX_REGISTER;
    static const int MAX_MEMORY;

    void clear();

    bool get_start() const { return Start; };
    void set_start() { Start = true; };

    bool get_halt() const { return Halt; };
    void set_halt() { Halt = true; };

    counter_t get_program_counter() const { return ProgramCounter; };
    void set_program_counter(counter_t value) { ProgramCounter = value; };
    void inc_program_counter(counter_t value = 1) { ProgramCounter += value; };

    register_t get_register(index_t register_index) const { return Register[register_index]; };
    void set_register(index_t register_index, register_t value) { Register[register_index] = value; };

    memory_t get_memory(address_t address) const { return Memory[address]; };
    memory_t* get_memory_data() { return Memory.data(); };
    void set_memory(address_t address, memory_t value) { Memory[address] = value; };

    counter_t get_label(const std::string& label_name) const;
    bool is_label(const std::string& label_name) const { return Label.find(label_name) != Label.end(); };
    void set_label(const std::string& label_name, counter_t value);

    function_t get_lib_function(const std::string& function_name) const;
    void link_lib_function(const std::string& function_name);
    void load_lib(const std::string& lib_name);

private:
    bool Halt, Start;
    counter_t ProgramCounter;
    std::vector<register_t> Register;
    std::vector<memory_t> Memory;
    std::map<std::string, counter_t> Label;

    std::map<std::string, lib_t> LibHandle;
    lib_t LastHandle;
    std::map<std::string, function_t> LibFunction;
};


#endif
