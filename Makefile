ifeq ($(OS),Windows_NT)
    FLAGS =
else
    FLAGS = -ldl
endif
FILES = src/main.cpp src/svm.cpp src/strutil.cpp src/library.cpp src/memory.cpp src/parser.cpp
OUT = bin/svm
COMPILE = g++ $(FILES) -o $(OUT) $(FLAGS)
all:
	$(COMPILE) -O2
debug:
	$(COMPILE) -D DEBUG
