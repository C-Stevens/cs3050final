CS3050 Final Project
Team members:
    * Colin Stevens - cjsd32@mail.missouri.edu
-------------------------

HOW TO RUN THIS PROGRAM:
    - Included with this submission is a Makefile. To build the program, navigate to the source directory (the directory this file is contained in), and use the `make` command.
        ex.     $ make
                gcc -g -Wall src/main.c -c
                gcc -g -Wall src/file_io.c -c
                gcc -g -Wall src/trade.c -c
                gcc -g -Wall main.o file_io.o trade.o -o bin/cjsd32FinalProj
    - After the program is built, you can run the compiled binary stored in <BUILD SOURCE DIRECTORY>/bin/cjsd32FinalProj
        ex.     $ ./bin/cjsd32FinalProj 6 4 prices.txt
        
EXPECTED COMMAND LINE ARGUMENTS:
    - The program will not run, or will not run correctly if the following arguments are not supplied in order: number of trade days, `r` parameter, price input filename.
        ex.     $ ./bin/cjsd32FinalProj 6 3 prices.txt

PROGRAM BEHAVIORS
    - If there are issues with the number of command line arguments, the following error will be raised to stdout: "Error: Incorrect number of command line arguments."
    - If there is an issue with the provided input file *opening*, the following error will be raised to stdout: "Error: File could not be opened."
        - In the above two examples, a usage message will print along with the error to provide you with the information in the EXPECTED COMMAND LINE ARGUMENTS section.
    - If there is an issue with writing the output strategy to the current directory (most likely bad perms on your machine), the following error will be raised to stdout : "Error: Was unable to create a file for strategy writing."
    - If there is an issue closing the input file after reading (unlikely), the following error will be raised to stdout: "Error: Failed to close file."
    - If there is an issue parsing: See PARSING section

PARSING
    - The input file (as specified in the project description) is to be formatted with a digit followed by a newline. Input matching is made with fscanf(). If fscanf is unable to match the expected number of
      inputs per line (1/one), the following error will be raised to stdout: "Error: Invalid input data detected."

EXIT CODES
    - When appropriate, this project makes use of the exit codes defined by the enum provided in previous assignments. These mappings can be found in <BUILD SOURCE DIR>/include/input_error.h

OUTPUT
    - Since the project document specifies output both as a "file" and mentions stdout, both are used to record output due to this abiguity. This means that on a successful determination of a trading strategy, to *BOTH* stdout and to a
      file called "strategy.txt", output will be written according to the following scheme (as specified in the project document):
            b1
            s1
            b2
            s2
            ...
            bn
            sn
       That is to say, alternating buy/sell pairs, with each individual buy/sell suffixed with a newline.

MISC. NOTES
    - The program **has** been verified to compile on Linux machines with standard gcc installations.
    - The program has been tested and verified to work the the project document's example input and correct strategy outputs with r input values 1-3.
    - If you think any of the above are not accurate, please email me at the address at the beginning of this document. I'm sure any issues can be explained and given greater context.

EXAMPLE OUTPUTS / PROOFS:
    - This output assumes the input file example provided with the project document.
    ex.     % ./bin/cjsd32FinalProj 6 1 prices.txt                                                   
                1
                6
    ex.     % ./bin/cjsd32FinalProj 6 2 prices.txt
                1
                4
                5
                6
    ex.     % ./bin/cjsd32FinalProj 6 3 prices.txt
                1
                4
                5
                6

PROJECT REPORT
    - EFFORTS ENTAILED
        * File input and parsing, with proper closure of files.
        * Error checking for file i/o, parsing, etc.
        * Dynamic array creation and conversion to static, fixed array for input prices
        * Creation of mapping "dictionary", with accompanying helper functions (builders, freeers, calculating key indices, etc.).
        * Ideal trade scheme calculation algorithm,
    - ALGORITHM COMPLEXITY
        * Various methods in the project are at least O(n) complexity. Methods with this complexity involve any "builders", or iterative functions that must run through an entire list.
            ex. Conversion of price linked list to static array of integers requires seeking through the entire list of prices to copy over values.
        * Trading algorithm(s) employ a complexity of O(<number of input days> * <number of input days> * <number of input days> * <given R value>), equally: O(d^3*r).
    - MEMBER CONTRIBUTIONS
        * Everything: Colin Stevens - cjsd32@mail.missouri.edu