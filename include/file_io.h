#ifndef H_FILEIO_H
#define H_FILEIO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct prices {
    int size;
    int* priceArray;
} prices;

typedef struct tmp {
    int size;
    struct tmpNode* head;
    struct tmpNode* tail;
} tmp;

typedef struct tmpNode {
    int val;
    struct tmpNode* next;
} tmpNode;

void freeTmp(tmp*);
prices* parseInputFile(char*);

#endif