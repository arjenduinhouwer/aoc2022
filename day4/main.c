#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

//#define FILENAME "../sample.txt"
#define FILENAME "../input.txt"

int set[4] = {-1};

void push(int value) {
    for (size_t i = 0; i < sizeof(set)/4; ++i) {
        if(set[i] <= 0) {
            set[i] = value;
            break;
        }
    }
}

size_t getInt(char line[], size_t s)
{
    size_t end;

    for (int i = s; i < 100; ++i) {
        if(line[i] == 44 || line[i] == 45 || line[i] == '\0') {
           end = i;
           break;
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
    push(result);
    return end;

}

void calculate_result_for_line(int *score) {
    if(set[1] < set[2] || set[0] > set[3]) {
        //
    } else {
        printf("%d - %d, %d - %d\n", set[0], set[1], set[2], set[3]);
        *score += 1;
    }

//    if((set[0] <= set[2] && set[1] >= set[3]) || (set[0] >= set[2] && set[1] <= set[3])) {
//
//        //printf("%d - %d, %d - %d\n", set[0], set[1], set[2], set[3]);
//        //printf("Score: %d\n", *score);
//    }
}
void clear_set(void)
{
    for (size_t i = 0; i < sizeof(set); ++i) {
        set[i] = -1;
    }
}

void split(char line[])
{
    char *p;
    char *p1, *p2;
    p = strtok(line, ",");
    if(p) {
        p1 = p;
        p = strtok(NULL, ",");
        p2 = p;
    }

    char *s;

    s = strtok(p1, "-");

    if(s) {
        set[0] = atoi(s);
        s = strtok(NULL, "-");
        set[1] = atoi(s);
    }

    char *s2;
    s2 = strtok(p2, "-");
    if(s2) {
        set[2] = atoi(s2);
        s2 = strtok(NULL, "-");
        set[3] = atoi(s2);
    }
}

void handle_line(char line[], int *score)
{
    split(line);
    calculate_result_for_line(score);
    clear_set();
}

void read_file()
{
    FILE *f = fopen(FILENAME, "r");
    if(ferror(f)) {
        printf("Could not read file");
        fclose(f);
    }

    char line[256];

    int score = 0;
    while(fgets(line, sizeof(line), f)) {
        if(strlen(line) == 1) {
            printf("End\n");
        }

        handle_line(line, &score);
    }
    printf("Score: %d\n", score);
    fclose(f);
}

int main(void)
{
    read_file();
//    printf("Total score: %d\n", *total_score);
    return 0;
}