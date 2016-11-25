all: main.o character.o item.o fanGame.o board.o
	g++ -std=c++11 main.o character.o item.o fanGame.o board.o -g -o fantasyGameBinary
	
clean:
	rm -rf *.o fantasyGameBinary

#compile main
main: main.cpp
	g++ -std=c++11 main.cpp -c

#compile character.cpp into outputfile
character: character.h character.cpp
	g++ -std=c++11 character.h character.cpp -g -c

#compile item.cpp into outputfile
item: item.h item.cpp
	g++ -std=c++11 item.h item.cpp -g -c

#complie fangame.cpp into outputfile
fanGame: fanGame.h fanGame.cpp 
	g++ -std=c++11 fanGame.h fanGame.cpp -g -c

#compile board.cpp into outputfile
board: board.h board.cpp
	g++ -std=c++11 board.h board.cpp -g -c


