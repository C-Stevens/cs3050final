#ifndef H_TRADE_H
#define H_TRADE_H

#include <stdio.h>
#include <stdlib.h>
#include "./file_io.h"

#define FALSE 0
#define TRUE 1

typedef struct trade {
    int buyDay;
    int sellDay;
} trade;

typedef struct tradeScheme {
    short initialized; // Used to track if this struct in the map. If placed in the map deliberately, it will be initialized (TRUE). If it is a generic key generated when building the map, it will be uninitialized (FALSE).
    int potential;
    int tradeListSize;
    trade* trades;
} tradeScheme;

typedef struct mapKey {
    int day1;
    int day2;
    int r;
} mapKey;

// Trading algorithms
tradeScheme* makeTradeScheme(int overallR, int numDays, prices* prices); // trade(r, prices)
tradeScheme* tryTrade(tradeScheme* map, int numDays, int* prices, int day1, int day2, int r); // tryTrade(day1, day2, r)
trade* combineTradeLists(tradeScheme* t1, tradeScheme* t2);

// Mapping functions
tradeScheme* makeTradeMap(int numDays, int overallR);
int getIndexOfKey(int numDays, mapKey* key);
int isInMap(tradeScheme* map, int numDays, mapKey* key);
void freeMapLists(tradeScheme* map, int numDays, int overallR);

#endif