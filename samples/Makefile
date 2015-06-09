ifeq ($(OS),Windows_NT)
    EXT = .dll
    DELETE = del
else
    EXT = .so
    DELETE = rm
endif

all: libhello libsample

libhello: libhello.c
	gcc -c -fpic libhello.c -o libhello.o
	gcc -shared -o libhello$(EXT) libhello.o
	$(DELETE) *.o

libsample: libsample.c
	gcc -c -fpic libsample.c -o libsample.o
	gcc -shared -o libsample$(EXT) libsample.o
	$(DELETE) *.o
