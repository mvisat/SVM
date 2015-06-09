#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// uses target, ignore src
void acak(int* target, int src, char* memory){
	srand (time(NULL));
	*target = rand() % 65536;
}

// uses src, ignore target, read memory
// print memory start from memory[src] until \0 character as string, followed by \n
void println(int* target, int src, char* memory){
    while (memory[src] != 0){
        printf("%c", memory[src]);
		src++;
	}
	printf("\n");
}
