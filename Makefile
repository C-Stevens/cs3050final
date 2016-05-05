CFLAGS = -g -Wall
OUTFILE = cjsd32FinalProj

cjsd32HW4: main.o file_io.o trade.o
	gcc $(CFLAGS) main.o file_io.o trade.o -o bin/$(OUTFILE)

main.o: src/main.c
	gcc $(CFLAGS) src/main.c -c

file_io.o: src/file_io.c
	gcc $(CFLAGS) src/file_io.c -c

trade.o: src/trade.c
	gcc $(CFLAGS) src/trade.c -c

clean:
	rm -f *.o bin/$(OUTFILE)
