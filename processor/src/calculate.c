#include "calculate.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calculate(char *file, char *phrase)
{
	FILE * fp;
        //char book[50];
        //char chapter[50];
        //char heading[1000];
        char *content;
        char *res;
        int sz;
        fp = fopen(file,"r");
        //res = fgets(book, 50, (FILE*)fp);
        //res = fgets(chapter, 50, (FILE*)fp);
        //res = fgets(heading,1000, (FILE*)fp);
        fseek(fp, 0L, SEEK_END);
        sz = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        content = (char *)calloc(sz, sizeof(char));

        res = fgets(content, sz, (FILE*)fp);
        fclose(fp);
        char *sub = strstr(content, phrase);
        int count = 0;
        while(3){
                if(sub == NULL) break;
                count++;
                sub++;
                sub = strstr(sub,phrase);
        }
        free(content);
        return count;
}

