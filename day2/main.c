#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//#define FILENAME "../sample.txt"
#define FILENAME "../input.txt"

char points[3] = {
        'X',
        'Y',
        'Z'
};

char options[3] = {
        'A',
        'B',
        'C'
};

int get_index_for_move(int player, char move)
{
    if(player == 1) {
        for (int i = 0; i < 3; ++i) {
            if(move == options[i]) {
                return i;
            }
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            if(move == points[i])
                return i;
        }
    }
}

int get_win(int p1)
{
    if(p1 == 0) { //rock
        return 1; //paper
    }

    if(p1 == 1) { //paper
        return 2; //scissors
    }

    if(p1 == 2) { //scissors
        return 0; //rock
    }

}

int get_lose(int p1)
{
    if(p1 == 0) { //rock
        return 2; //scissors
    }

    if(p1 == 1) { //paper
        return 0; //stone
    }

    if(p1 == 2) { //scissors
        return 1; //paper
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

    int totalPoints = 0;
    while(fgets(line, sizeof(line), f)) {
        if(strlen(line) == 1) {
            printf("End\n");
        }

        int p1 = get_index_for_move(1,line[0]);
        int p2 = get_index_for_move(2,line[2]);
        printf("p1 - %d\n", p1);
        int newP2;

        //x = lose 0
        //y = draw 1
        //z = win  2

        if(p2 == 0) {
            newP2 = get_lose(p1);
            printf("Play lose\n");
            totalPoints += 0;
        }

        if(p2 == 1) {
            newP2 = p1;
            printf("Play draw\n");
            totalPoints += 3;
        }

        if(p2 == 2) {
            newP2 = get_win(p1);
            printf("Play win\n");
            totalPoints += 6;
        }

        printf("p2 - %d\n", newP2);
        printf("----------------\n");


        totalPoints += (newP2+1);//add the score for chosen option

        //not 14907 || 11612
//        printf("subtotal points: %d\n", totalPoints);
    }
    fclose(f);
    printf("Total: %d\n", totalPoints);
}

int main(void) {
    read_file();
    return 0;
}