capizero: ./src/capizero.o ./src/board.o ./src/generate.o 
	@ g++ -o capizero ./src/capizero.o ./src/board.o ./src/generate.o

capizero.o: ./src/capizero.cpp
	@ g++ -c ./src/capizero.cpp -o ./src/capizero.o

generate.o: ./src/generate.cpp
	@ g++ -c ./src/generate.cpp -o ./src/generate.o

board.o: ./src/board.cpp
	@ g++ -c ./src/board.cpp -o ./src/board.o

clean:
	@ del src\*.o

all: capizero clean