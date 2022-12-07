#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//#define FILENAME "../sample.txt"
#define FILENAME "../input.txt"

bool chunk_has_doubles(const char chunk[]) {
    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 14; ++j) {
            if(i == j)
                continue;

            //printf("Check %c: against:%c\n", chunk[i], chunk[j]);
            if(chunk[i] == chunk[j])
                return true;
        }
    }

    return false;
}

void handle_line(char line[])
{
    for (int i = 13; i < strlen(line); ++i) {
        bool found = true;
        char chunk[14] = {0};
//        if(i > 66 && i < 70)
//            exit(1);

        int cnt = 0;
        for (int j = i-13; j <= i; ++j) {
            printf("Add %c to chunk j = %d\n", line[j], j);
            chunk[cnt] = line[j];
            cnt++;
        }

        if(chunk_has_doubles(chunk)) {
            printf("Doubles found\n\n");
            continue;
        } else {
            printf("No doubles found\n");
            printf("answer = %d\n", i+1);
            exit(1);
            break;
        }
        printf("-----------\n\n");
    }
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
//    char chunk[4] = {'A', 'B', 'D', 'C'};
//    if(chunk_has_doubles(chunk)) {
//        printf("Yes\n");
//    } else {
//        printf("Noe\n");
//    }

    read_file();
    return 0;
}