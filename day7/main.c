#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define FILENAME "../sample.txt"
//#define FILENAME "../input.txt"

typedef struct Node Node;

struct Node {
    Node *parent;
    Node *children;
    char type;
    size_t size;
};

typedef  struct {
    size_t size;
    Node nodes[1024];
} Node_Pool;

static Node_Pool node_pool = {0};

void handle_line(char line[])
{
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

void print_tree(Node_Pool *np)
{
    for (int i = 0; i < 2; ++i) {
        Node *n = &np->nodes[i];
        printf("%c -> %zu\n", n->type, n->size);
    }
};

Node *node_pool_alloc(Node_Pool *np)
{
    Node *result = &np->nodes[np->size];
    np->size += 1;
    return result;
}

int main(void)
{
    Node *s1 = node_pool_alloc(&node_pool);
    s1->type = 'f';
    s1->size = 512;

    print_tree(&node_pool);
//    read_file();
    return 0;
}