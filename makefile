all:
	g++ board.h board.cpp main.cpp -o fantasyGameBinary

clean:
	rm -rf *o fantasyGameBinary
