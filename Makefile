CFLAGS = -IHeaders -Wall -O2 -g
HEADERS = ma.h Auxiliares.h
CC = gcc
OBJ = main.o ma.o

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)
program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm *.o
	rm program
