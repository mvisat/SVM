#include "invoker.hpp"

using namespace std;

invoker::invoker(): mapOfCommandCode(MAX_COMMAND) {
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
    mnemonic_t mnemonic = static_cast<mnemonic_t>(cmd[pointer]);
    command *c = mapOfCommandCode[mnemonic];
    if (c != 0) {
        c->execute(cmd);
    }
    else {
        throw svm_exception("Error: Invalid bytecode 0x" + to_hex(static_cast<unsigned>(mnemonic)) + " at " + to_string(pointer));
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
