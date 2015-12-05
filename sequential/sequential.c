#include<stdio.h>
#include<string.h>
#include "calculate.c"

int main(int argc, char *argv[])
{
	char *file = argv[1];
	char *phrase = argv[2];
	int result = calculate(file, phrase);
	printf("%s appears %d times\n",phrase,result);

}
