CFLAGS = -g -Wall
OUTFILE = cjsd32FinalProj

cjsd32HW4: main.o
	gcc $(CFLAGS) main.o -o bin/$(OUTFILE)

main.o: src/main.c
	gcc $(CFLAGS) src/main.c -c

clean:
	rm *.o bin/$(OUTFILE)
