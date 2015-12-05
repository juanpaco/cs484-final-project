#include<stdio.h>
#include<string.h>

int calculate(char *file, char *phrase)
{
	FILE * fp;
        char book[50];
        char chapter[50];
        char heading[1000];
        char content[9000];
        fp = fopen(file,"r");
        fgets(book, 9000, (FILE*)fp);
        fgets(chapter, 9000, (FILE*)fp);
        fgets(heading,9000, (FILE*)fp);
        fgets(content,9000, (FILE*)fp);
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

