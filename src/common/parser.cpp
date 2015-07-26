#include "parser.hpp"

vector<vector<string> > parse_file(const string& filename) {
    ifstream input(filename.c_str());
    if (input.is_open()) {
        vector<vector<string> > syntax;
        string s;
        while (getline(input, s)) {
            vector<string> v = str_split_ws(s);
            for (unsigned int i = 0; i < v.size(); ++i) {
                if (v[i] == "#") {
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
                    cout << syntax[i][j] << " ";
                cout << endl;
            }
        #endif

        input.close();
        return syntax;
    }
    else {
        throw svm_exception("Error: Failed to read file '" + filename + "'");
    }
}

int parse_register(const string& s) {
    if (s.size() > 1 && s[0] == '$')
        try {
            int reg = from_string<int>(s.substr(1));
            if (reg >= 0 && reg < memory::MAX_REGISTER)
                return reg;
        } catch (const exception&) {

        }
    throw svm_exception("Error: Invalid register '" + s + "'");
}

constant_t parse_constant(const string& s) {
    if (s.size() > 0)
        try {
            int c = from_string<int>(s);
            return c;
        } catch (const exception&) {

        }
    throw svm_exception("Error: Invalid constant '" + s + "'");
}

string parse_function(const string& s) {
    if (s.size() > 1 && s[0] == '@')
        return s.substr(1);
    throw svm_exception("Error: Invalid function '" + s + "'");
}
