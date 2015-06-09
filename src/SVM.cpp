#include "SVM.hpp"

const int SVM::MaxRegister = 16;
const int SVM::MaxMemory = 65536;

SVM::SVM() {

}

SVM::SVM(const string& FileName) {
    Load(FileName);
}

SVM::~SVM() {

}

void SVM::Load(const string& FileName) {
    Syntax.clear();
    ifstream input(FileName.c_str());
    if (input.is_open()) {
        string s;
        while (getline(input, s)) {
            vector<string> v = StrSplitByWhitespace(s);
            if (v.size())
                Syntax.push_back(v);
        }
    }
}

void SVM::Initialize() {
    Halt = false;
    ProgramCounter = 0;

    Register.clear();
    for (int i = 0; i < MaxRegister; ++i)
        Register.push_back(0);

    Memory.clear();
    for (int i = 0; i < MaxMemory; ++i)
        Memory.push_back(0);

    Label.clear();
    for (int i = 0; i < Syntax.size(); ++i) {
        if (Syntax[i][0].substr(0, 1) == ".") {
            Label[Syntax[i][0]] = i;
        }
    }
}

void SVM::Run() {
    if (Syntax.size() == 0)
        return;

    Initialize();
    while (ProgramCounter < Syntax.size() && !Halt) {
        #ifdef DEBUG
            cout << "Run:: " << ProgramCounter << " ";
            for (int i = 0; i < Syntax[ProgramCounter].size(); ++i)
                cout << Syntax[ProgramCounter][i] << " ";
            cout << endl;
        #endif
        Process(Syntax[ProgramCounter]);
        #ifdef DEBUG
            for (int i = 0; i < MaxRegister; ++i)
                cout << "$" << i << " = " << Register[i] << endl;
            cout << endl;
        #endif
    }
}

void SVM::Process(const vector<string>& cmd) {
    if (cmd[0] == "start" || cmd[0] == "#") {
        // Do nothing
    }
    else if (cmd[0] == "halt") {
        Halt = true;
    }
    else if (cmd[0] == "add") {
        CmdAdd(ParseRegister(cmd[1]), ParseRegister(cmd[2]), ParseRegister(cmd[3]));
    }
    else if (cmd[0] == "addi") {
        CmdAddImmediate(ParseRegister(cmd[1]), ParseRegister(cmd[2]), StrToInt(cmd[3]));
    }
    else if (cmd[0] == "sub") {
        CmdSubstract(ParseRegister(cmd[1]), ParseRegister(cmd[2]), ParseRegister(cmd[3]));
    }
    else if (cmd[0] == "mul") {
        CmdMultiply(ParseRegister(cmd[1]), ParseRegister(cmd[2]), ParseRegister(cmd[3]));
    }
    else if (cmd[0] == "and") {
        CmdAnd(ParseRegister(cmd[1]), ParseRegister(cmd[2]), ParseRegister(cmd[3]));
    }
    else if (cmd[0] == "or") {
        CmdOr(ParseRegister(cmd[1]), ParseRegister(cmd[2]), ParseRegister(cmd[3]));
    }
    else if (cmd[0] == "not") {
        CmdNot(ParseRegister(cmd[1]), ParseRegister(cmd[2]));
    }
    else if (cmd[0] == "eq") {
        CmdEqual(ParseRegister(cmd[1]), ParseRegister(cmd[2]), ParseRegister(cmd[3]));
    }
    else if (cmd[0] == "lt") {
        CmdLessThan(ParseRegister(cmd[1]), ParseRegister(cmd[2]), ParseRegister(cmd[3]));
    }
    else if (cmd[0] == "gt") {
        CmdGreaterThan(ParseRegister(cmd[1]), ParseRegister(cmd[2]), ParseRegister(cmd[3]));
    }
    else if (cmd[0] == "ld") {
        CmdLoad(ParseRegister(cmd[1]), ParseRegister(cmd[2]), StrToInt(cmd[3]));
    }
    else if (cmd[0] == "lb") {
        CmdLoadByte(ParseRegister(cmd[1]), ParseRegister(cmd[2]), StrToInt(cmd[3]));
    }
    else if (cmd[0] == "ldi") {
        CmdLoadImmediate(ParseRegister(cmd[1]), StrToInt(cmd[2]));
    }
    else if (cmd[0] == "str") {
        CmdStore(ParseRegister(cmd[1]), ParseRegister(cmd[2]), StrToInt(cmd[3]));
    }
    else if (cmd[0] == "stb") {
        CmdStoreByte(ParseRegister(cmd[1]), ParseRegister(cmd[2]), StrToInt(cmd[3]));
    }
    else if (cmd[0] == "jz") {
        CmdJumpIfZero(ParseRegister(cmd[1]), cmd[2]);
    }
    else if (cmd[0] == "jnz") {
        CmdJumpIfNotZero(ParseRegister(cmd[1]), cmd[2]);
    }
    else if (cmd[0] == "jmp") {
        CmdJump(cmd[1]);
    }
    else if (cmd[0] == "jr") {
        CmdJumpRegister(ParseRegister(cmd[1]));
    }
    else if (cmd[0] == "jal") {
        CmdJumpAndLink(ParseRegister(cmd[1]), cmd[2]);
    }
    else if (cmd[0] == "libc") {
        CmdLibraryCall(ParseRegister(cmd[1]), ParseRegister(cmd[2]), cmd[3]);
    }
    ++ProgramCounter;
}

int SVM::ParseRegister(const string& s) {
    return StrToInt(s.substr(1));
}

void SVM::CmdAdd(int rDest, int rSrc1, int rSrc2) {
    Register[rDest] = Register[rSrc1] + Register[rSrc2];
}

void SVM::CmdAddImmediate(int rDest, int rSrc, int C) {
    Register[rDest] = Register[rSrc] + C;
}

void SVM::CmdSubstract(int rDest, int rSrc1, int rSrc2) {
    Register[rDest] = Register[rSrc1] - Register[rSrc2];
}

void SVM::CmdMultiply(int rDest, int rSrc1, int rSrc2) {
    Register[rDest] = Register[rSrc1] * Register[rSrc2];
}

void SVM::CmdAnd(int rDest, int rSrc1, int rSrc2) {
    Register[rDest] = Register[rSrc1] && Register[rSrc2];
}

void SVM::CmdOr(int rDest, int rSrc1, int rSrc2) {
    Register[rDest] = Register[rSrc1] || Register[rSrc2];
}

void SVM::CmdNot(int rDest, int rSrc) {
    Register[rDest] = !Register[rSrc];
}

void SVM::CmdEqual(int rDest, int rSrc1, int rSrc2) {
    Register[rDest] = Register[rSrc1] == Register[rSrc2];
}

void SVM::CmdLessThan(int rDest, int rSrc1, int rSrc2) {
    Register[rDest] = Register[rSrc1] < Register[rSrc2];
}

void SVM::CmdGreaterThan(int rDest, int rSrc1, int rSrc2) {
    Register[rDest] = Register[rSrc1] > Register[rSrc2];
}

void SVM::CmdLoad(int rDest, int rSrc, int C) {
    Register[rDest] = Memory[Register[rSrc] + C] | (Memory[Register[rSrc] + C + 1] << 8);
}

void SVM::CmdLoadByte(int rDest, int rSrc, int C) {
    Register[rDest] = Memory[Register[rSrc] + C];
}

void SVM::CmdLoadImmediate(int rDest, int C) {
    Register[rDest] = C;
}

void SVM::CmdStore(int rDest, int rSrc, int C) {
    Memory[Register[rSrc] + C] = Register[rDest] & 0xFF;
    Memory[Register[rSrc] + C + 1] = Register[rDest] & 0xFF00;
}

void SVM::CmdStoreByte(int rDest, int rSrc, int C) {
    Memory[Register[rSrc] + C] = Register[rDest] & 0xFF;
}

void SVM::CmdJumpIfZero(int rDest, const string& label) {
    if (Register[rDest] == 0)
        ProgramCounter = Label[label];
}

void SVM::CmdJumpIfNotZero(int rDest, const string& label) {
    if (Register[rDest] != 0)
        ProgramCounter = Label[label];
}

void SVM::CmdJump(const string& label) {
    ProgramCounter = Label[label];
}

void SVM::CmdJumpRegister(int rDest) {
    ProgramCounter = Register[rDest];
}

void SVM::CmdJumpAndLink(int rDest, const string& label) {
    Register[rDest] = ProgramCounter+1;
    ProgramCounter = Label[label];
}

void SVM::CmdLibraryCall(int rDest, int rSrc, const string& func) {
    if (func == "@input") {
        short in;
        cin >> in;
        Register[rDest] = in;
    }
    else if (func == "@output") {
        cout << Register[rSrc] << endl;
    }
}
