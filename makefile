all:
	g++ character.h board.h fanGame.h character.cpp board.cpp fanGame.cpp  main.cpp -g -o fantasyGameBinary

clean:
	rm -rf *o fantasyGameBinary
