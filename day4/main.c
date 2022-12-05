#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "../sample.txt"
//#define FILENAME "../input.txt"

int total_score = 0;

size_t getInt(char line[], size_t s)
{
    size_t end;

    for (int i = s; i < 100; ++i) {
        if(line[i] == 44 || line[i] == 45) {
           end = i;
        }
    }

    size_t length = end-s;
    char sub[length];

    size_t cnt = 0;
    for (int j = s; j < end; ++j) {
        sub[cnt] = line[j];
        cnt++;
    }

    int result = atoi(sub);
//    printf("result = %d\n", result);

    return end;

}

int handle_line(char line[])
{
    size_t length = strlen(line)-1;

    for (size_t i = 0; i < length; ++i) {
        if(line[i] != 44 && line[i] != 45) {
            i = getInt(line, i)+1;
            printf("%zu\n", i);
        }
    }

    return 0;
}

void read_file()
{
    FILE *f = fopen(FILENAME, "r");
    if(ferror(f)) {
        printf("Could not read file");
        fclose(f);
    }

    char line[256];

    while(fgets(line, sizeof(line), f)) {
        if(strlen(line) == 1) {
            printf("End\n");
        }

        total_score += handle_line(line);
    }
    fclose(f);
}

int main(void) {
    read_file();
    printf("Total score: %d\n", total_score);
    return 0;
}