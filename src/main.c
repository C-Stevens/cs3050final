#include <stdlib.h>
#include <stdio.h>
#include "../include/file_io.h"
#include "../include/input_error.h"

int main(int argc, char** argv) {
    if(argc != 4) {
        printf("Error: Incorrect number of command line arguments.\n");
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    parseInputFile(argv[3]);
}