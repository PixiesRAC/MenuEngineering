CC=g++
CFLAGS= -std=c++11 -Wall -pedantic
EXEC=Server

all: $(EXEC)

Server: main.o Server.o
	$(CC) -o Server Server.o main.o

Server.o: ServerEngMenu.cpp
	$(CC) -o Server.o -c ServerEngMenu.cpp $(CFLAGS)

main.o: main.cpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
