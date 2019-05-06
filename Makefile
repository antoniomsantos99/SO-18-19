CFLAGS = -IHeaders -Wall -O2 -g
HEADERS = ma.h Auxiliares.h
CC = gcc
OBJ = main.o ma.o
OBJSV = sv.o Auxiliares.o
OBJCV = cv.o
OBJTESTES = criaCasosTeste.o

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)
all: program sv cv casosTestes
program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
sv: $(OBJSV)
	$(CC) -o $@ $^ $(CFLAGS)
cv: $(OBJCV)
	$(CC) -o $@ $^ $(CFLAGS)
casosTestes: $(OBJTESTES)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm *.o
	rm -f program
	rm -f sv
	rm -f cv
	rm -f casosTestes
