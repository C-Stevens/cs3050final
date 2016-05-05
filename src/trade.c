#include "../include/trade.h"

tradeScheme* makeTradeMap(int numDays, int r) {
    int sizeOfList = numDays * numDays * r;
}

int getIndexOfKey(int numDays, int overallR, mapKey* key) {
    return (key->day1 + (numDays * key->day2)) + (key->r * (numDays * overallR));
}