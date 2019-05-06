CFLAGS = -IHeaders -Wall -O2 -g
HEADERS = ma.h Auxiliares.h
CC = gcc
OBJ = main.o ma.o
OBJSV = sv.o Auxiliares.o
OBJCV = cv.o

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)
program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
sv: $(OBJSV)
	$(CC) -o $@ $^ $(CFLAGS)
cv: $(OBJCV)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm *.o
	rm program
	rm sv
	rm cv
