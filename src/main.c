#include <stdlib.h>
#include <stdio.h>
#include "../include/file_io.h"
#include "../include/trade.h"
#include "../include/input_error.h"

void printUsage(char** argv) {
    printf("\tUsage: %s <number of trade days> <`r` parameter> <input filename>\n", argv[0]);
}

int main(int argc, char** argv) {
    /* argv[0] : program path
     * argv[1] : number of days
     * argv[2] : `r` parameter
     * argv[3] : input filename
     */
    if(argc != 4) {
        printf("Error: Incorrect number of command line arguments.\n");
        printUsage(argv);
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    prices* prices = parseInputFile(argv[3]);
//     if(prices->size != atoi(argv[1])) {
//         printf("Error: Number of days entered does not match the number of predicted stocks on days in the input file (%d days expected, %d days found in input file)\n", atoi(argv[1]), prices->size);
//         printUsage(argv);
//         exit(PARSING_ERROR_INVALID_FORMAT);
//     }
    
    
    tradeScheme* scheme = makeTradeScheme(atoi(argv[2]), atoi(argv[1]), prices);
    FILE* output = fopen("strategy.txt", "w");
    if(output == NULL) {
        printf("Error: Was unable to create a file for strategy writing.\n");
        exit(FILE_FAILED_TO_OPEN);
    }
    
    int i, buyDay, sellDay;
    for(i=0; i<scheme->tradeListSize; i++) {
        buyDay = scheme->trades[i].buyDay + 1; // Offset by +1 to convert away from array indices
        sellDay = scheme->trades[i].sellDay + 1; // Ditto
        printf("%d\n%d\n", buyDay, sellDay);
        fprintf(output, "%d\n%d\n", buyDay, sellDay);
    }
    
    fclose(output);
}