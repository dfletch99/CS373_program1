CFLAGS = -Wall -Wextra -DDEBUG -g -std=c++14

all: main.o State.h Machine.h
	g++ -o fletcher_p1 main.o
	
main.o:
	g++ -c $(CFLAGS) main.cpp -o main.o

clean:
	rm -rf *.o fletcher_p1
