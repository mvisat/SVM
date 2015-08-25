#ifndef COMMON_LIBRARY_H
#define COMMON_LIBRARY_H

#ifdef _WIN32
    #include <windows.h>
    typedef HMODULE lib_t;
    typedef FARPROC proc_t;
#else
    #include <dlfcn.h>
    typedef void* lib_t;
    typedef void* proc_t;
#endif

lib_t LibLoad(const char* szLib);
int LibUnload(lib_t hLib);
proc_t LoadProc(lib_t hLib, const char* szProc);

#endif
