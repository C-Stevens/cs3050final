#ifndef H_TRADE_H
#define H_TRADE_H

#include <stdio.h>
#include <stdlib.h>
#include <file_io.h>

#define FALSE 0
#define TRUE 1

typedef struct trade {
    int buyDay;
    int sellDay;
} trade;

typedef struct tradeScheme {
    int potential;
    int tradeListSize;
    trade* trades;
} tradeScheme;

typedef struct mapKey {
    int day1;
    int day2;
    int r;
} mapKey;

tradeScheme* makeTradeScheme(int r, int* prices); // trade(r, prices)
tradeScheme* tryTrade(int* prices, int day1, int day2, int r); // tryTrade(day1, day2, r)

// Mapping functions
tradeScheme* makeTradeMap(void);
int getIndexOfKey(mapKey* key);
int isInMap(mapKey* key);

#endif