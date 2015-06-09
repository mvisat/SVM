FILES = src\Main.cpp src\SVM.cpp src\StrUtil.cpp
OUT = bin\SVM
all:
	g++ $(FILES) -o $(OUT)
debug:
	g++ $(FILES) -o $(OUT) -D DEBUG
