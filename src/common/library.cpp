#include "library.hpp"

lib_t LibLoad(const char* szLib) {
#ifdef _WIN32
    return ::LoadLibraryA(szLib);
#else
    return ::dlopen(szLib, RTLD_LAZY);
#endif
}

int LibUnload(lib_t hLib) {
#ifdef _WIN32
    return ::FreeLibrary(hLib);
#else
    return ::dlclose(hLib);
#endif
}

proc_t LoadProc(lib_t hLib, const char* szProc) {
#ifdef _WIN32
    return ::GetProcAddress(hLib, szProc);
#else
    return ::dlsym(hLib, szProc);
#endif
}
