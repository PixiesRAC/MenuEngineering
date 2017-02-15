CC=g++ 
CFLAGS= -std=c++11 -Wall -pedantic
LDFLAGS=
EXEC=Customer

all: $(EXEC)

Customer: main.o Customer.o
	$(CC) -o Customer Customer.o main.o $(LDFLAGS)

Customer.o: Customer.cpp
	$(CC) -o Customer.o -c Customer.cpp $(CFLAGS)

main.o: main.cpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
