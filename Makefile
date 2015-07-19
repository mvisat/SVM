ifeq ($(OS),Windows_NT)
    FLAGS =
else
    FLAGS = -ldl
endif
FILES = src/Main.cpp src/SVM.cpp src/StrUtil.cpp src/LibCall.cpp
OUT = bin/svm
COMPILE = g++ $(FILES) -o $(OUT) $(FLAGS)
all:
	$(COMPILE) -O2
debug:
	$(COMPILE) -D DEBUG
