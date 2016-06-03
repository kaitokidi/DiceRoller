# Makefile super op

all: main.o everything exe

main.o: *.cpp
	g++ -c -std=c++11 *.cpp	
	
everything:
	g++ -o game *.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
		
exe:
	./game
	
clear:
	rm *.o
