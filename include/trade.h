#ifndef H_TRADE_H
#define H_TRADE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct trade {
    int day1;
    int day2;
} trade;

typedef struct tradeScheme {
    int potential;
    int tradeListSize;
    struct trade* trades;
} tradeScheme;

#endif