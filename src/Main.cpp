#include "SVM.hpp"

using namespace std;

int main() {
    string FileName;
    cout << "Enter SASM file name: ";
    cin >> FileName;
    SVM svm(FileName);
    svm.Run();

    return 0;
}
