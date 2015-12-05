#include "calculate.h"

#include<stdio.h>
#include<string.h>

int calculate(char *file, char *phrase)
{
	FILE * fp;
        char book[50];
        char chapter[50];
        char heading[1000];
        char content[9000];
        char *res;
        fp = fopen(file,"r");
        res = fgets(book, 50, (FILE*)fp);
        res = fgets(chapter, 50, (FILE*)fp);
        res = fgets(heading,1000, (FILE*)fp);
        res = fgets(content,9000, (FILE*)fp);
        fclose(fp);
        char *sub = strstr(content, phrase);
        int count = 0;
        while(3){
                if(sub == NULL) break;
                count++;
                sub++;
                sub = strstr(sub,phrase);
        }
        return count;
}

