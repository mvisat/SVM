ifeq ($(OS),Windows_NT)
    EXT = .dll
    DEL = del /S /F
else
    EXT = .so
    DEL = rm -rf
endif

all: libhello libsample

libhello: libhello.c
	gcc -fPIC -c libhello.c -o libhello.o
	gcc -fPIC -shared -o libhello$(EXT) libhello.o
	@$(DEL) *.o

libsample: libsample.c
	gcc -fPIC -c libsample.c -o libsample.o
	gcc -fPIC -shared -o libsample$(EXT) libsample.o
	@$(DEL) *.o
