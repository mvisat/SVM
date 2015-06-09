#include "SVM.hpp"

#include <exception>
#include <iostream>

using namespace std;

int main() {
    string FileName;
    cout << "Enter SASM file name: ";
    cin >> FileName;
    try {
        SVM svm(FileName);
        svm.Run();
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
