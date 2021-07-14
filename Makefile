capizero: ./src/capizero.o ./src/board.o ./src/generate.o ./src/attacks.o ./src/perft.o ./src/benchmark.o ./src/search.o
	@ g++ -o capizero ./src/capizero.o ./src/board.o ./src/generate.o ./src/attacks.o ./src/perft.o ./src/benchmark.o ./src/search.o

perft.o: ./src/perft.cpp
	@ g++ -c ./src/perft.cpp -o ./src/perft.o

capizero.o: ./src/capizero.cpp
	@ g++ -c ./src/capizero.cpp -o ./src/capizero.o

generate.o: ./src/generate.cpp
	@ g++ -c ./src/generate.cpp -o ./src/generate.o

attacks.o: ./src/attacks.cpp
	@ g++ -c ./src/attacks.cpp -o ./src/attacks.o

board.o: ./src/board.cpp
	@ g++ -c ./src/board.cpp -o ./src/board.o

benchmark.o: ./src/benchmark.cpp
	@ g++ -c ./src/benchmark.cpp -o ./src/benchmark.o

search.o: ./src/search.cpp
	@g++ -c ./src/search.cpp -o ./src/search.o

clean:
	@ del src\*.o

all: capizero clean