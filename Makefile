CFLAGS = -IHeaders -Wall -O2 -g
HEADERS = ma.h Auxiliares.h
CC = gcc
OBJDIR = obj
OBJ = ma.o Auxiliares.o
OBJSV = sv.o Auxiliares.o
OBJCV = cv.o
OBJTESTES = criaCasosTeste.o

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)
all: ma sv cv casosTestes
ma: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
sv: $(OBJSV)
	$(CC) -o $@ $^ $(CFLAGS)
cv: $(OBJCV)
	$(CC) -o $@ $^ $(CFLAGS)
casosTestes: $(OBJTESTES)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm -f *.o
	rm -f ma
	rm -f sv
	rm -f cv
	rm -f casosTestes
	rm -f ServerCall
	rm -f ClientCall
