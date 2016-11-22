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
//initialise a matrix of character locations

FantasyGame::FantasyGame(int rows,int cols) {
	// Initlialize the random number generator
	time_t qTime;
	time(&qTime);
	srand((unsigned int)qTime);
    //generate a new board
	board newBoard(rows, cols);
    //used to resize the initialised matrix to the correct number of rows
    CharacterLocation.resize(rows);
    for (int i = 0; i < rows; i++){
        //used to resize the initialised matrix to the correct number of colunms
        CharacterLocation[i].resize(cols);
    }
    // setting all values in the matrix to 0 as 0 is empty space
    for (unsigned int Row = 0; Row < 10; ++Row) {
        for (unsigned int Col = 0; Col < 10; ++Col) {
            CharacterLocation[Row][Col]    = 0;
        }
    }

    bool startPos = false;
	while (!startPos) {
		unsigned int Row = 1;
		unsigned int Col = 1;
		if (QueryLocation(Row, Col) == 0) {
			startPos = true;
            //setting up the player a point (1,1) in the matrix
			CharacterLocation[Row][Col] = &Player;
		}
	}
	// Create 10 Enemies
	bool startPos2 = false;
	unsigned int foe = 6;
	while (!startPos2) {
		unsigned int Row = 2 + (rand() % (rows - 2));
		unsigned int Col = 2 + (rand() % (cols - 2));
        //randomly generating 10 enemies needs to be updated
		if (QueryLocation(Row, Col) == 0) {
			CharacterLocation[Row][Col] = &Enemies[foe];
			++foe;
			if (foe == 16) {
				startPos2 = true;
			}
	    }
	}
}
//Used to find out wether an enemy,player or blank space is at each location
int FantasyGame::QueryLocation(unsigned int Row, unsigned int Col) {
    for (unsigned int i = 6; i < 16; ++i) {
        //if the location is an enemy reutrn 6-16 for enemies
        if (CharacterLocation[Row][Col] == &(Enemies[i])) {
            return i;
        }
    }
    //if player location return 3
    if (CharacterLocation[Row][Col] == &Player) {
         return 3;
    //else return the board value wall(5) or empty space(0)
    } else {
        return board::map[Row][Col];
    }
}
//this needs to be updated so it doesn't have a hardcoded 20 rather the correct rows and cols
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
    //locates the player and sets up a temporary location
	unsigned int NextRow = PlayerRow;
	unsigned int NextCol = PlayerCol;
    //uses a switch statement to move
    //Moves by taking and adding to the row and col
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
    //queries the players next location
	int NextLoc = QueryLocation(NextRow, NextCol);
    //if empty moves player to that location
	if (NextLoc == 0) {
		CharacterLocation[NextRow][NextCol] = &Player;
		CharacterLocation[PlayerRow][PlayerCol] = 0;
		return true;
    //if an enemy player will attack that enemy
	} else if (NextLoc >= 6 && NextLoc <= 16) {
		Player.Attack(Enemies[NextLoc]);
		return true;
     //if not enemy or player returns false as it is a wall
	} else {
		return false;
	}
}
//checks if player is dead
bool FantasyGame::PlayerIsDead() {
	return Player.IsDead();
}
//removes dead enemies
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
//checks wether all foes are dead if so gameover
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


