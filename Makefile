FLAGS = -ldl
FILES = src/Main.cpp src/SVM.cpp src/StrUtil.cpp src/LibCall.cpp
OUT = bin/SVM
COMPILE = g++ $(FILES) -o $(OUT) $(FLAGS)
all:
	$(COMPILE) -O2
debug:
	$(COMPILE) -D DEBUG
