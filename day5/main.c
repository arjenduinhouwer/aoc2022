#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//#define FILENAME "../sample.txt"
#define FILENAME "../input.txt"

#define COLS  9
#define COL_CAPACITY 1000

//char crates[COLS][COL_CAPACITY] = {{'Z', 'N'}, {'M', 'C', 'D'}, {'P'}};
char crates[COLS][COL_CAPACITY] = {
        {'T', 'P', 'Z', 'C', 'S', 'L', 'Q', 'N'},
        {'L', 'P', 'T', 'V', 'H', 'C', 'G'},
        {'D', 'C', 'Z', 'F'},
        {'G', 'W', 'T', 'D', 'L', 'M', 'V', 'C'},
        {'P', 'W', 'C'},
        {'P', 'F', 'J', 'D', 'C', 'T', 'S', 'Z'},
        {'V', 'W', 'G', 'B', 'D'},
        {'N', 'J', 'S', 'Q', 'H', 'W'},
        {'R', 'C', 'Q', 'F', 'S', 'L', 'V'}
};

void draw_stack() {
    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < COL_CAPACITY; ++j) {
            if(isprint(crates[i][j])) {
                printf("[%c]", crates[i][j]);
            } else {break;}
        }
        printf("\n");
    }
    printf("\n====================\n");

}

void move_crate(size_t from, size_t to, size_t index)
{
    char to_move = crates[from][index];

    for (size_t j = 0; j < COL_CAPACITY; ++j) {
        if(!isprint(crates[to][j])){
            crates[to][j] = to_move;
            break;
        }
    }
}

void prepare_move_crate(size_t from, size_t to, size_t amount) {
    size_t end;
    for(size_t i = 0; i < COL_CAPACITY; ++i) {
//        printf("%zu\n", i);
        if(!isprint(crates[from][i+1])){
            end = i;
            break;
        }
    }

    size_t start = end-(amount-1);
//    printf("%zu -> %zu: %zu\n", start, end, amount);

    if(amount == 1) {
        move_crate(from, to, end);
    } else {
        for (size_t j = start; j <= end; ++j) {
            printf("Move %zu from %zu to %zu vanaf index %zu\n", amount, from , to, j);
            move_crate(from, to, j);
        }
    }

    if(amount == 1) {
        for (size_t i = end; i < COL_CAPACITY; ++i) {
            crates[from][i] = -1;
        }
    } else {
        for (size_t k = start; k < COL_CAPACITY; ++k) {
            crates[from][k] = -1;
        }
    }

    draw_stack();
}

void handle_line(char line[])
{
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

    prepare_move_crate(src-1, dest-1, amount);

}

void get_message()
{
    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < COL_CAPACITY; ++j) {
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
    int cnt = 0;
    while(fgets(line, sizeof(line), f)) {
//        if(cnt == 2)
//            break;

        if(strlen(line) == 1) {
            printf("End\n");
        }
//        cnt++;
        handle_line(line);
    }
    fclose(f);
}

int main(void)
{
    draw_stack();
//    exit(1);
    read_file();
    draw_stack();
    get_message();
    return 0;
}