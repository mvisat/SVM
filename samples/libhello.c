#include <stdio.h>

// ignore src & target
void hello(int* target, int src, char* memory){
	printf("hello world!\n");
}

// read from memory, use src & target
// read n = memory[src], sum memory[src+1] to memory[src+n]
void sum(int* target, int src, char* memory){
	int i; int n; *target = 0;
	src = (int) ((unsigned short) src);
	n = memory[src];
	for (i = 1; i <= n; ++i){
		*target += memory[src + i];
	}
}