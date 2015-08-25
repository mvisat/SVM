#include "parser.hpp"

std::vector<std::vector<std::string> > parse_file(const std::string& filename) {
    std::ifstream input(filename.c_str());
    if (input.is_open()) {
        std::vector<std::vector<std::string> > syntax;
        std::string s;
        while (getline(input, s)) {
            std::vector<std::string> v = str_split_ws(s);
            for (unsigned int i = 0; i < v.size(); ++i) {
                if (v[i].size() == 0 || v[i][0] == '#') {
                    while (i < v.size())
                        v.erase(v.begin()+i);
                    break;
                }
            }
            if (v.size())
                syntax.push_back(v);
        }

        #ifdef DEBUG
            for (unsigned int i = 0; i < syntax.size(); ++i) {
                for (int j = 0; j < syntax[i].size(); ++j)
                    std::cout << syntax[i][j] << " ";
                std::cout << endl;
            }
        #endif

        input.close();
        return syntax;
    }
    else {
        throw svm_exception("Error: Failed to read file '" + filename + "'");
    }
}

int parse_register(const std::string& s) {
    if (s.size() > 1 && s[0] == '$')
        try {
            int reg = from_string<int>(s.substr(1));
            if (reg >= 0 && reg < memory::MAX_REGISTER)
                return reg;
        } catch (const std::exception&) {

        }
    throw svm_exception("Error: Invalid register '" + s + "'");
}

constant_t parse_constant(const std::string& s) {
    if (s.size() > 0)
        try {
            int c = from_string<int>(s);
            return c;
        } catch (const std::exception&) {

        }
    throw svm_exception("Error: Invalid constant '" + s + "'");
}

std::string parse_function(const std::string& s) {
    if (s.size() > 1 && s[0] == '@')
        return s.substr(1);
    throw svm_exception("Error: Invalid function name '" + s + "'");
}
