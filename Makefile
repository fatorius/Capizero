capizero: capizero.o board.o 
	@ g++ -o capizero capizero.o board.o

capizero.o: capizero.cpp
	@ g++ -c capizero.cpp -o capizero.o

board.o: board.cpp
	@ g++ -c board.cpp -o board.o

clean:
	@ del *.o

all: capizero clean