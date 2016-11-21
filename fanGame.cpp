#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
#include "character.h"
#include "board.h"
#include "fanGame.h"
using namespace std;

vector< vector<character*> > FantasyGame::CharacterLocation(10,vector<character*>(10));
//board newBoard(int rows, int cols);
FantasyGame::FantasyGame(int rows,int cols) {
	// Initlialize the random number generator
	time_t qTime;
	time(&qTime);
	srand((unsigned int)qTime);
	board newBoard(rows, cols);
    CharacterLocation.resize(rows);
    for (int i = 0; i < rows; i++){
        CharacterLocation[i].resize(cols);
    }
        for (unsigned int Row = 0; Row < 10; ++Row) {
            for (unsigned int Col = 0; Col < 10; ++Col) {
                CharacterLocation[Row][Col]    = 0;
            }
        }


    bool startPos = false;
	while (!startPos) {
		unsigned int Row = 1;
        //+ (rand() % 8);
		unsigned int Col = 1;
		// + (rand() % 8);
		if (QueryLocation(Row, Col) == 0) {
			startPos = true;
			CharacterLocation[Row][Col] = &Player;
		}
	}
	// Create 10 Enemies
	bool startPos2 = false;
	unsigned int foe = 6;
	while (!startPos2) {
		unsigned int Row = 2 + (rand() % (rows - 2));
		unsigned int Col = 2 + (rand() % (cols - 2));
		if (QueryLocation(Row, Col) == 0) {
			CharacterLocation[Row][Col] = &Enemies[foe];
			++foe;
			if (foe == 16) {
				startPos2 = true;
			}
		}
	}
}

int FantasyGame::QueryLocation(unsigned int Row, unsigned int Col) {
    for (unsigned int i = 6; i < 16; ++i) {
        if (CharacterLocation[Row][Col] == &(Enemies[i])) {
            return i;
        }
    }
    if (CharacterLocation[Row][Col] == &Player) {
         return 3;
    } else {
        return board::map[Row][Col];
    }
}

bool FantasyGame::LocateCharacter(unsigned int& rRow, unsigned int& cCol,character* xyCharacter) {
	for (unsigned int Row = 0; Row < 20; ++Row) {
		for (unsigned int Col = 0; Col < 20; ++Col) {
			if (CharacterLocation[Row][Col] == xyCharacter) {
				rRow = Row;
				cCol = Col;
				return true;
			}
		}
	}
	return false;
}

bool FantasyGame::MovePlayer(const char Movement) {
	unsigned int PlayerRow;
	unsigned int PlayerCol;
	LocateCharacter(PlayerRow, PlayerCol, &Player);
	unsigned int NextRow = PlayerRow;
	unsigned int NextCol = PlayerCol;
	switch (Movement) {
        case 'w':
		case 'W':
			{
				--NextRow;
				break;
			}
        case 'd':  
		case 'D':
			{
				++NextCol;
				break;
			}
        case 's':
		case 'S':
			{
				++NextRow;
				break;
			}
        case 'a':
		case 'A':
			{
				--NextCol;
				break;
			}
		default:
			{
				return false;
			}
	}
	int NextLoc = QueryLocation(NextRow, NextCol);
	if (NextLoc == 0) {
		CharacterLocation[NextRow][NextCol] = &Player;
		CharacterLocation[PlayerRow][PlayerCol] = 0;
		return true;
	} else if (NextLoc >= 6 && NextLoc <= 16) {
		Player.Attack(Enemies[NextLoc]);
		return true;
	} else {
		return false;
	}
}

bool FantasyGame::PlayerIsDead() {
	return Player.IsDead();
}

void FantasyGame::RemoveDeadFoes() {
	for (unsigned int i = 6; i < 16; ++i) {
		if (Enemies[i].IsDead()) {
			unsigned int Row;
			unsigned int Col;
			if (LocateCharacter(Row, Col,&(Enemies[i]))) {
				CharacterLocation[Row][Col] = 0;
				std::cout << "Enemy Killed!" << std::endl;
			}
		}
	}
}

bool FantasyGame::AllFoesDead() {
	bool AllDead = true;
	for (unsigned int i = 6; i < 16; ++i) {
		if (!Enemies[i].IsDead()) {
			AllDead = false;
		}
	}
	return AllDead;
}

void FantasyGame::PrintBoard(int Rows,int Cols) {
// display the map, just a simple loop
for (int down = 0; down < Rows; down++) {
	for (int across = 0; across < Cols; across++) {
		switch(QueryLocation(down, across))
		{
			case 0:  // Nothing
				cout << " ";
			break;
			case 1:  // item
				cout << "$";
			break;
			case 6 ... 16: //Enemy
				cout << "E";
			break;
			case 3: //player
				cout << "P";
			break;
			case 5:  // wall
				cout << "#";
			break;
		}
	}
	cout << endl;
}

}


