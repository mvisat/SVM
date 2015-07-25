#include "interpreter.hpp"

#include <exception>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == string("-kei")) {
            interpreter interpreter;
            string filename;
            if ((i+1) >= argc) {
                cerr << "Error: -kei requires kei file" << endl;
            }
            else {
                try {
                    interpreter.run_kei(string(argv[i+1]));
                    return 0;
                }
                    catch (const exception& e) {
                    cerr << e.what() << endl;
                }
            }
            return 1;
        }
        else {
            try {
                interpreter interpreter;
                interpreter.run_sasm(string(argv[i]));
                return 0;
            }
            catch (const exception& e) {
                cerr << e.what() << endl;
            }
            return 1;
        }
    }
    cerr << "Usage:\tsvm sasmfile" << endl;
    cerr << "\t    (to execute a sasm file)" << endl;
    cerr << "    or\tsvm -kei keifile" << endl;
    cerr << "\t    (to execute a kei file)" << endl;
    return 1;
}
