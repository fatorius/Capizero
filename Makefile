capizero: ./src/capizero.o ./src/board.o 
	@ g++ -o capizero ./src/capizero.o ./src/board.o

capizero.o: ./src/capizero.cpp
	@ g++ -c ./src/capizero.cpp -o ./src/capizero.o

board.o: ./src/board.cpp
	@ g++ -c ./src/board.cpp -o ./src/board.o

clean:
	@ del src\*.o

all: capizero clean