all:
	g++ character.h item.h board.h fanGame.h character.cpp item.cpp board.cpp fanGame.cpp  main.cpp -g -o fantasyGameBinary

clean:
	rm -rf *o fantasyGameBinary
