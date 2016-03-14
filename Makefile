CFLAGS = -g -Wall
OUTFILE = cjsd32HW3

cjsd32HW3: main.o graph.o
	gcc $(CFLAGS) main.o graph.o -o bin/$(OUTFILE)

main.o: src/main.c
	gcc $(CFLAGS) src/main.c -c

graph.o: src/graph.c
	gcc $(CFLAGS) src/graph.c -c

clean:
	rm *.o bin/$(OUTFILE)
