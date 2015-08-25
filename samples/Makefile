ifeq ($(OS),Windows_NT)
    EXT = .dll
    DEL = del /S /F
else
    EXT = .so
    DEL = rm -rf
endif

all: libhello libsample

libhello: libhello.c
	gcc -c libhello.c -o libhello.o -m32
	gcc -shared -o libhello$(EXT) libhello.o -m32
	@$(DEL) *.o

libsample: libsample.c
	gcc -c libsample.c -o libsample.o -m32
	gcc -shared -o libsample$(EXT) libsample.o -m32
	@$(DEL) *.o
