CC = gcc
CFLAGS = -Wall -g

# target executable
TARGET = hotel

# object files
OBJ = main.o hotel.o

# default rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# compile main
main.o: main.c hotel.h
	$(CC) $(CFLAGS) -c main.c

# compile hotel
hotel.o: hotel.c hotel.h
	$(CC) $(CFLAGS) -c hotel.c

# clean build files
clean:
	rm -f *.o $(TARGET)