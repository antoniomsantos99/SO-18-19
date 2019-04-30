CFLAGS = -IHeaders -Wall -O2 -g
HEADERS =
CC = gcc
OBJ = main.o

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)
program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm *.o
	rm program
