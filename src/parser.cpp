#include "parser.hpp"

int parseRegister(const string& s) {
    if (s.size() > 1 && s[0] == '$')
        try {
            int reg = strConvert<int>(s.substr(1));
            if (reg >= 0 && reg < memory::MAX_REGISTER)
                return reg;
        } catch (const exception&) {

        }
    throw svm_exception("Error: Invalid register '" + s + "'");
}

constant_t parseConstant(const string& s) {
    if (s.size() > 0)
        try {
            int c = strConvert<int>(s);
            return c;
        } catch (const exception&) {

        }
    throw svm_exception("Error: Invalid constant '" + s + "'");
}
