#include "svm.hpp"

#include <exception>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        string fileName(argv[1]);
        try {
            svm svm(fileName);
            svm.run();
            return 0;
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }
        return 1;
    }
    else {
        cout << "Usage:\tsvm [sasm file]" << endl;
    }
    return 0;
}
