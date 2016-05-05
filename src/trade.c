#include "../include/trade.h"

tradeScheme* makeTradeMap(int numDays, int overallR) {
    /* Construct a mapping array of tradeScheme structs to hold and track what schemes have already
     * been made/attempted by the algorithm.
     */
    int sizeOfList = numDays * numDays * overallR; // Max key pool size
    tradeScheme* map = malloc(sizeof(tradeScheme) * sizeOfList);
    int i;
    for(i=0; i<sizeOfList; i++) { // Mark all members as untouched/uninitialized
        map[i].initialized = FALSE;
    }
    
    return map;
}

void freeMapLists(tradeScheme* map, int numDays, int overallR) {
    /* Free the created trade arrays at tradeSchemes that have been set by the algorithm.
     */
    int sizeOfList = numDays * numDays * overallR;
    int i;
    for(i=0; i<sizeOfList; i++) {
        if(map[i].initialized == TRUE) { // Free the trade array if this scheme has been set
            free(map[i].trades);
        }
    }
}

int getIndexOfKey(int numDays, mapKey* key) {
    /* Returns the index of the provided key in the mapping array by flattening the key into a 
     * single index value.
     */
    return (key->day1 + (numDays * key->day2)) + (key->r * (numDays * numDays));
}

int isInMap(tradeScheme* map, int numDays, mapKey* key) {
    /* Determines if the scheme in the map at the index of the provided key has been initialized/
     * set by the algorithm (has been visited).
     */
    if(map[getIndexOfKey(numDays, key)].initialized == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

trade* combineTradeLists(tradeScheme* t1, tradeScheme* t2) {
    /* Combines and returns the trade lists of two schemes t1 and t2.
     */
    trade* newList = malloc(sizeof(trade) * (t1->tradeListSize + t2->tradeListSize));

    int i, j; // Add the first list
    for(i=0; i<(t1->tradeListSize); i++) {
        newList[i] = t1->trades[i];
    }
    int k = 0; // Add the second list to where the first list left off
    for(j=(t1->tradeListSize); j<(t1->tradeListSize + t2->tradeListSize); j++) {
        newList[j] = t2->trades[k];
        k++;
    }
    return newList;
}

tradeScheme* tryTrade(tradeScheme* map, int numDays, int* priceArray, int day1, int day2, int r) {
    // Create the key to used for mapping
    mapKey* currentKey = malloc(sizeof(mapKey));
    currentKey->day1 = day1;
    currentKey->day2 = day2;
    currentKey->r = r;
    
    // Initialize a trading scheme
    tradeScheme* scheme = malloc(sizeof(tradeScheme));
    scheme->initialized = TRUE;
    scheme->potential = 0;
    scheme->tradeListSize = 0;
    scheme->trades = NULL; // No trades yet
    
    if(isInMap(map, numDays, currentKey) == TRUE) { // We've been here before, just return the computed scheme
        return &map[getIndexOfKey(numDays, currentKey)];
    }
    if(day1 == day2) { // There's no scheme work to be done since the days are the same
        return scheme;
    }
    
    if(r > 1) {
        int i, j, total;
        for(i=day1; i<(day2+1); i++) {
            for(j=1; j<(r); j++) {
                // Construct two potential schemes, one offset by i, j and day1, the other by i, day2, and r-j
                tradeScheme* t1 = tryTrade(map, numDays, priceArray, day1, i, j);
                tradeScheme* t2 = tryTrade(map, numDays, priceArray, i+1, day2, r-j);
                total = t1->potential + t2->potential;
                if(scheme->potential < total) { // We have a better scheme
                    scheme->potential = total;
                    // Combine both t1 & t2 trade arrays into a single array, then set scheme->trades to this (remember to set tradeListSize)
                    scheme->trades = combineTradeLists(t1, t2);
                    scheme->tradeListSize = (t1->tradeListSize + t2->tradeListSize);
                }
            }
        }

    } else { // r < 1, otherwise just as well said as if r == 1
        // Figure out the best scheme in a single buy and sell pair
        int buyDay, sellDay;
        buyDay = sellDay = -1; // -1 = unset
        int i,j, diff;
        for(i=day1; i<(day2+1); i++) {
            for(j=i; j<(day2+1); j++) {
                diff = priceArray[j] - priceArray[i];
                if(scheme->potential < diff) {
                    scheme->potential = diff;
                    buyDay = i;
                    sellDay = j;
                }
            }
        }
        
        if(buyDay != -1 && sellDay != -1) { // We've found a buy/sell pair
            trade* trade = malloc(sizeof(trade));
            trade->buyDay = buyDay;
            trade->sellDay = sellDay;
            scheme->tradeListSize = 1;
            scheme->trades = trade; // Attach the single buy/sell trade scheme to our trading scheme struct
        }
    }
    
    map[getIndexOfKey(numDays, currentKey)] = *scheme; // "Save" our computation in the map
    return scheme;
    
}

tradeScheme* makeTradeScheme(int overallR, int numDays, prices* prices) {
    tradeScheme* map = makeTradeMap(numDays, overallR);
    tradeScheme* scheme = tryTrade(map, numDays, prices->priceArray, 0, (prices->size - 1), overallR);
    freeMapLists(map, numDays, overallR);
    return scheme;
}