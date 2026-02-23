CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
LDFLAGS = -lm

TARGET = kurs
OBJ = main.o functions.o methods.o tests.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

main.o: main.c functions.h methods.h tests.h
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

methods.o: methods.c methods.h functions.h
	$(CC) $(CFLAGS) -c methods.c

tests.o: tests.c tests.h methods.h
	$(CC) $(CFLAGS) -c tests.c

clean:
	rm -f $(OBJ) $(TARGET)
