#include "invoker.hpp"

using namespace std;

invoker::invoker(): mapOfCommandCode(OPCODE_MAX) {
}

void invoker::add(command *c) {
    if (c != 0) {
        mapOfCommandName[c->name()] = c;
        mapOfCommandCode[c->mnemonic_code()] = c;
    }
}

void invoker::execute(const vector<string>& cmd) {
    map<string, command*>::iterator it = mapOfCommandName.find(cmd[0]);
    if (it != mapOfCommandName.end()) {
        command *c = it->second;
        if (cmd.size() ==  c->operand_size())
            c->execute(cmd);
        else
            throw svm_exception("Error: Invalid number of operands for '" + c->name() + "'");
    }
    else if (cmd[0][0] != '.') {
        throw svm_exception("Error: Invalid syntax '" + cmd[0] + "'");
    }
}

void invoker::execute(const vector<bytecode_t>& cmd, counter_t pointer) {
    bytecode_t code = cmd[pointer];
    command *c;
    if (code >= 0 && code < OPCODE_MAX && (c = mapOfCommandCode[code]) != 0) {
        c->execute(cmd);
    }
    else {
        throw svm_exception("Error: Invalid bytecode 0x" + to_hex(static_cast<unsigned>(code)) + " at " + to_string(pointer));
    }
}

void invoker::write_bytecode(const vector<string>& cmd) {
    map<string, command*>::iterator it = mapOfCommandName.find(cmd[0]);
    if (it != mapOfCommandName.end()) {
        command *c = it->second;
        if (cmd.size() ==  c->operand_size())
            return c->write_bytecode(cmd);
        else
            throw svm_exception("Error: Invalid number of operands for '" + c->name() + "'");
    }
    else if (cmd[0][0] != '.') {
        throw svm_exception("Error: Invalid syntax '" + cmd[0] + "'");
    }
}
