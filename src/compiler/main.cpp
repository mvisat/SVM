#include "compiler.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Usage:\tsvmc [sasm files]" << endl;
        return 1;
    }

    compiler compiler;
    for (int i = 1; i < argc; ++i) {
        try {
            compiler.compile(string(argv[i]));
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
            return 1;
        }
    }
    return 0;
}
