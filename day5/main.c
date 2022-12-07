#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define FILENAME "../sample.txt"
//#define FILENAME "../input.txt"

char crates[3][10] = {{'Z', 'N'}, {'M', 'C', 'D'}, {'P'}};
//char crates[9][1000] = {
//        {'T', 'P', 'Z', 'C', 'S', 'L', 'Q', 'N'},
//        {'L', 'P', 'T', 'V', 'H', 'C', 'g'},
//        {'D', 'C', 'Z', 'F'},
//        {'G', 'W', 'T', 'D', 'L', 'M', 'V', 'C'},
//        {'P', 'W', 'C'},
//        {'P', 'F', 'J', 'D', 'C', 'T', 'S', 'Z'},
//        {'V', 'W', 'G', 'B', 'D'},
//        {'N', 'J', 'S', 'Q', 'H', 'W'},
//        {'R', 'C', 'Q', 'F', 'S', 'L', 'V'}
//};

void draw_stack() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 1000; ++j) {
            if(isprint(crates[i][j]))
                printf("[%c]", crates[i][j]);
        }
        printf("\n");
    }
    printf("\n====================\n");

}

void move_crate(size_t from, size_t to, size_t amount)
{
    char to_move;
    for(size_t i = 0; i < 1000; ++i) {
        if(!isprint(crates[from][i+1])){
            to_move = crates[from][i];
            crates[from][i] = -1;
            break;
        }
    }

    for (size_t j = 0; j < 1000; ++j) {
        if(!isprint(crates[to][j])){
            crates[to][j] = to_move;
            break;
        }
    }
}

void handle_line(char line[])
{
    //move, amount, from, src, dest
//    printf("%s\n", line);
    char *p;
    char *current;
    size_t amount, src, dest = -1;
    p = strtok(line, " ");
    if(p) {
        current = strtok(NULL, " ");
        amount = atoi(current);
        current = strtok(NULL, " ");
        current = strtok(NULL, " ");
        src = atoi(current);
        current = strtok(NULL, " ");
        current = strtok(NULL, " ");
        dest = atoi(current);
    }

//    printf("amount: %zu\n", amount);
//    printf("src: %zu\n", src);
//    printf("dest: %zu\n", dest);

    for (size_t i = 0; i < amount; ++i) {
        move_crate(src-1, dest-1);
    }

//    draw_stack();
}

void get_message()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 1000; ++j) {
//            if(i = 2) {
//                printf("%c\n", crates[i][j]);
//            }
            if(!isprint(crates[i][j+1])) {
                printf("%c", crates[i][j]);
                break;
            }
        }
    }
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

        handle_line(line);
    }

    fclose(f);
}

int main(void)
{
//    draw_stack();
//    exit(1);
    read_file();
    draw_stack();
    get_message();
    return 0;
}