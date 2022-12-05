#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

//#define FILENAME "../sample.txt"
#define FILENAME "../input.txt"
int total_score = 0;

bool in_array(int letter, int arr[])
{
    for (int i = 0; i < 52; ++i) {
       if(arr[i] == letter) {
           return true;
       }
    }
    return false;
}

void insert_in_array(int letter, int arr[])
{
    for (int i = 0; i < 52; ++i) {
        if(arr[i] == -1)
            arr[i] = letter;
    }
}

int calc_score(int letter) {
    //small letters
    if(letter > 96) {
        return letter-96;
    } else {
       return letter-38;
    }

}

char handle_lines(char line1[], char line2[], char line3[]) {
    char shared_item = -1;
    for (int i = 0; i < strlen(line1)-1; ++i) {
        for (int j = 0; j < strlen(line2)-1; ++j) {
            if(line1[i] == line2[j]) {
                for (int k = 0; k < strlen(line3)-1; ++k) {
                    if(line1[i] == line3[k]) {
                        printf("Found something: %c\n", line1[i]);
                        shared_item = line1[i];
                        break;
                    }
                }
            }
            if(shared_item > -1)
                break;
        }
        if(shared_item > -1)
            break;
    }

//    printf("Shared item: %c\n", shared_item);
    return shared_item;

}

void read_file()
{
    FILE *f = fopen(FILENAME, "r");
    if(ferror(f)) {
        printf("Could not read file");
        fclose(f);
    }

    char line[256];

    char line1[256];
    char line2[256];
    char line3[256];

    int count = 0;
    while(fgets(line, sizeof(line), f)) {
        if(strlen(line) == 1) {
            printf("End\n");
        }

        if(count > 2) {
            count = 0;
        }

        if(count == 0) {
            strcpy(line1, line);
        }
        if(count == 1) {
            strcpy(line2, line);
        }
        if(count == 2) {
            strcpy(line3, line);
        }


        count++;
        if(count == 3) {
            char item = handle_lines(line1, line2, line3);
            total_score += calc_score(item);
        }

    }
    fclose(f);
}

int main(void) {
    read_file();
    printf("Total score = %d\n", total_score);
    return 0;
}