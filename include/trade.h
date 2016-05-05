#ifndef H_TRADE_H
#define H_TRADE_H

#include <stdio.h>
#include <stdlib.h>
#include <file_io.h>

typedef struct trade {
    int buyDay;
    int sellDay;
} trade;

typedef struct tradeScheme {
    int potential;
    int tradeListSize;
    trade* trades;
} tradeScheme;

tradeScheme* trade(int r, int* prices); // trade(r, prices)
tradeScheme* tryTrade(int day1, int day2, int r); // tryTrade(day1, day2, r)

#endif