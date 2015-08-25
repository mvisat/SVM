#include "compiler.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Usage:\tsvmc [sasm files]" << std::endl;
        return 1;
    }

    compiler compiler;
    for (int i = 1; i < argc; ++i) {
        try {
            compiler.compile(std::string(argv[i]));
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
