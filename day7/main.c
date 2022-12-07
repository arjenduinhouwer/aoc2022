#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define FILENAME "../sample.txt"
//#define FILENAME "../input.txt"

void handle_line(char line[])
{
    if(line[0] == '$') {
        //cd & ls
        if()
    }
    printf("%d\n", line[0]);
}


void read_file()
{
    FILE *f = fopen(FILENAME, "r");
    if(ferror(f)) {
        printf("Could not read file");
        fclose(f);
    }

    char line[4096];
    while(fgets(line, sizeof(line), f)) {
        if(strlen(line) == 1) {
            printf("End\n");
        }
//        printf("%s\n", line);
        handle_line(line);
    }
    fclose(f);
}


int main(void)
{
    read_file();
    return 0;
}