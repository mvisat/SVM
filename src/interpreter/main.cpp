#include "interpreter.hpp"

#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("-kei")) {
            interpreter interpreter;
            std::string filename;
            if ((i+1) >= argc) {
                std::cerr << "Error: -kei requires kei file" << std::endl;
            }
            else {
                try {
                    interpreter.run_kei(std::string(argv[i+1]));
                    return 0;
                }
                    catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            return 1;
        }
        else {
            try {
                interpreter interpreter;
                interpreter.run_sasm(std::string(argv[i]));
                return 0;
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            return 1;
        }
    }
    std::cerr << "Usage:\tsvm sasmfile" << std::endl;
    std::cerr << "\t    (to execute a sasm file)" << std::endl;
    std::cerr << "    or\tsvm -kei keifile" << std::endl;
    std::cerr << "\t    (to execute a kei file)" << std::endl;
    return 1;
}
