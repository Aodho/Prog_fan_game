#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
#include "character.h"
#include "board.h"
#include "fanGame.h"
#include "item.h"
#include <map>
using namespace std;

vector< vector<character*> > FantasyGame::CharacterLocation(10,vector<character*>(10));
//initialise a matrix of character locations
vector< vector<item*> > FantasyGame::ItemLocation(10,vector<item*>(10));
//initialise a matrix of item locations
vector<item> FantasyGame::inventory(0);
//map<int,item> pickedUpItems;

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
    ItemLocation.resize(rows);
    for (int i = 0; i < rows; i++){
        //used to resize the initialised matrix to the correct number of colunms
        ItemLocation[i].resize(cols);
    }
    // setting all values in the matrix to 0 as 0 is empty space
    for (unsigned int Row = 0; Row < 10; ++Row) {
        for (unsigned int Col = 0; Col < 10; ++Col) {
            CharacterLocation[Row][Col]    = 0;
        }
    }
    // setting all values in the matrix to 0 as 0 is empty space
    for (unsigned int Row = 0; Row < 10; ++Row) {
        for (unsigned int Col = 0; Col < 10; ++Col) {
            ItemLocation[Row][Col]    = 0;
        }
    }
    inventory.clear();

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
	//Create 10 Items
	bool genItems = false;
    unsigned int item = 17;
    while (!genItems) {
        unsigned int Row = 2 + (rand() % (rows - 2));
        unsigned int Col = 2 + (rand() % (cols - 2));
        //randomly generating 10 items needs to be updated
        if (QueryLocation(Row, Col) == 0) {
            ItemLocation[Row][Col] = &Items[item];
            Items[item - 17].setUpItem(1+(rand()%8));
            ++item;
            if (item == 27) {
                genItems = true;
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
	for (unsigned int j = 17; j < 27; ++j) {
		if (ItemLocation[Row][Col] == &(Items[j])) {
            return j;
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

bool FantasyGame::checkItemType(unsigned int CurLoc){
    for (int j = 0;j<inventory.size(); ++j){
        if(inventory[j].getType() == Items[CurLoc - 17].getType()){
            return false;
        }
    }
    return true;
}
bool FantasyGame::checkInventorySpace(unsigned int CurLoc){
    unsigned int total = 0;
    for (int j = 0;j<inventory.size(); ++j){
        total = (total + inventory[j].getWeight());
    }
    if ((total + Items[CurLoc - 17].getWeight())>Player.getStrength())
    {
        return false;
    }
    return true;
}

bool FantasyGame::MovePlayer(const char Movement) {
	unsigned int PlayerRow;
	unsigned int PlayerCol;
	LocateCharacter(PlayerRow, PlayerCol, &Player);
    //locates the player and sets up a temporary location
	unsigned int NextRow = PlayerRow;
	unsigned int NextCol = PlayerCol;
    int CurLoc = QueryLocation(NextRow, NextCol);
    //uses a switch statement to move
    //Moves by taking and adding to the row and col
	switch (Movement) {
		case 'W':
			{
				--NextRow;
				break;
			}
		case 'D':
			{
				++NextCol;
				break;
			}
		case 'S':
			{
				++NextRow;
				break;
			}
		case 'A':
			{
				--NextCol;
				break;
			}
        case 'P':
            {
                if (CurLoc >= 17 && CurLoc <= 27){
                    if(checkItemType(CurLoc) == true){
                        if(checkInventorySpace(CurLoc) == true){
                        inventory.push_back(Items[CurLoc - 17]);
                        ItemLocation[PlayerRow][PlayerCol] = 0;
                        }else{
                          cout << "Not Strong enough to carry any more items \n";
                        }
                    }else{
                        cout << "Item of Type: " << Items[CurLoc - 17].getType() << " already present in inventory \n";
                        return false;
                    }
                    return true;
               }else{
                    return false;
               }
                break;
            }
        case 'O':
            {
                if (inventory.size() > 0){
                    cout << "INVENTORY: \n";
                    for (int j = 0;j<inventory.size(); ++j){
                       cout << j << "). " << inventory[j].getname() << ", Weight: " << inventory[j].getWeight()<< ", Attack: " << inventory[j].getAttack()<< ", Defense: " << inventory[j].getDefense()<< ", Strength: " << inventory[j].getStrength()<< ", Health: " << inventory[j].getHealth()<< "," << "\n";
                    }
                    if(CurLoc == 3){
						unsigned int x;
                        cout << "Please enter Item number from inventory list";
						cin >> x;
						inventory.erase(inventory.begin() + x);
                    }
                    else{
                        cout << "Unable to drop item as space is not free!";
                    }
                }
                else{
                    cout << "Nothing Present in inventory";
                }
             break;
            }
        case 'I':
            {
                cout << "INVENTORY: \n";
                if (inventory.size() > 0){
                    for (int j = 0;j<inventory.size(); ++j){
                       cout << j << "). " << inventory[j].getname() << ", Weight: " << inventory[j].getWeight() << ", Attack: " << inventory[j].getAttack()<< ", Defense: " << inventory[j].getDefense()<< ", Strength: " << inventory[j].getStrength()<<  ", Health: " << inventory[j].getHealth()<< "," << "\n";

                    }
                }
                else{
                    cout << "Nothing in inventory" << "\n";
                }
                return true;
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
	}else if (NextLoc >= 17 && NextLoc <= 27){ 
		CharacterLocation[NextRow][NextCol] = &Player;
		CharacterLocation[PlayerRow][PlayerCol] = 0;
		return true;
	}else if (NextLoc >= 6 && NextLoc <= 16) {
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
			case 17 ... 27:  // item
				cout << "$";
			break;
			case 6 ... 16: //Enemy
				cout << "I";
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


