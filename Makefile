CFLAGS = -g -Wall
OUTFILE = cjsd32FinalProj

cjsd32HW4: main.o file_io.o
	gcc $(CFLAGS) main.o file_io.o -o bin/$(OUTFILE)

main.o: src/main.c
	gcc $(CFLAGS) src/main.c -c

file_io.o: src/file_io.c
	gcc $(CFLAGS) src/file_io.c -c

clean:
	rm -f *.o bin/$(OUTFILE)
