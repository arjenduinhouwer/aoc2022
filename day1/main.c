#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//get the total of the top 3 highest calories

uint32_t top[3] = {0,0,0};

void calculate_total()
{
    uint32_t total = 0;
    for (int i = 0; i < 3; ++i) {
        printf("%d: %u\n", i, top[i]);
        total += top[i];
    }

    printf("Total = %u\n", total);
}

void insert_and_shift(uint32_t value) {
    printf("Insert: %u\n", value);
    int32_t last_val = -1;
    for(size_t i = 0; i < 3; ++i) {
        if(value < top[i])
            continue;

        if(top[i] < value) {
            if(last_val == -1) {
                last_val = top[i];
                top[i] = value;
                continue;
            }

            if(last_val > -1) {
                uint32_t cur = top[i];
                top[i] = last_val;
                last_val = cur;
            }
        }
    }

    calculate_total();
}

void read_file()
{
    FILE *f = fopen("../input.txt", "r");
    if(ferror(f)) {
        printf("Could not read file");
        fclose(f);
    }

    char line[256];

    uint32_t current_total = 0;
    while(fgets(line, sizeof(line), f)) {
        if(strlen(line) == 1) {
            if(current_total > top[2]) {
                //printf("ttl: %u\n", current_total);
                insert_and_shift(current_total);
            }
            current_total = 0;
        }

        current_total += atoi(line);
    }

    fclose(f);
}

int main(void) {
    read_file();
//    calculate_total();
    return 0;
}