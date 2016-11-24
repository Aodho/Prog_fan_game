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
//initialise a matrix of character pointers showing locations
vector< vector<item*> > FantasyGame::ItemLocation(10,vector<item*>(10));
//initialise a matrix of item pointers showing locations
vector<item> FantasyGame::inventory(0);

vector<character*> FantasyGame::orcs(0);
//A vecotr of inventory
vector< vector<item> > FantasyGame::Items(10,vector<item>(10));

vector< vector<character> > FantasyGame::Enemies(10,vector<character>(10));
unsigned int Gold = 0;

FantasyGame::FantasyGame(int rows,int cols) {

    int p = 0;
    while(p<1 || p>5){
    cout << "Please choose a race.\n" << "Select the corresponding number:\n" <<
            "1 For HUMAN\n2 For ELF\n3 For DWARF\n4 For HOBBIT\n5 for Orc\n"  <<endl;
    cin >> p;
    }
    cout << "Good Choice Young Padawan! You Have Chosen: " << p << endl;

//////This has to go here in order to happen before the board is created////////

	// Initlialize the random number generator
	time_t qTime;
	time(&qTime);
    setNight(false);
	srand((unsigned int)qTime);
    int squares = rows*cols;
    int tenPercent = (double)squares/(double)10;// * (1/10);
    //generate a new board
	board newBoard(rows, cols);
    //used to resize the initialised matrix to the correct number of rows
    ItemLocation.resize(rows);        
    CharacterLocation.resize(rows);
    Items.resize(rows);
    Enemies.resize(rows);
    for (int i = 0; i < rows; i++){
        //used to resize the initialised matrix to the correct number of colunms
        CharacterLocation[i].resize(cols);
        ItemLocation[i].resize(cols);
        Items[i].resize(cols);
        Enemies[i].resize(cols);
    }
    // setting all values in the matrix to 0 as 0 is empty space
    for (unsigned int Row = 0; Row < 10; ++Row) {
        for (unsigned int Col = 0; Col < 10; ++Col) {
            CharacterLocation[Row][Col] = 0;
            ItemLocation[Row][Col] = 0;
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
			Player.setUpCharacter(p);
            if (p == 5){
               orcs.push_back(&Player);
            }

		}
	}
	// Create 10 Enemies
	bool startPos2 = false;
	unsigned int foe = 1;
	while (!startPos2) {
		unsigned int Row = 2 + (rand() % (rows - 2));
		unsigned int Col = 2 + (rand() % (cols - 2));
        //randomly generating 10 enemies needs to be updated
		if (QueryLocation(Row, Col) == 0) {
            int x = 1+(rand()%5);
			CharacterLocation[Row][Col] = &Enemies[Row][Col];
			Enemies[Row][Col].setUpCharacter(x);
            if (x == 5){
            orcs.push_back(&Enemies[Row][Col]);
            }
			++foe;
			if (foe == tenPercent) {
				startPos2 = true;
			}
	    }
	}
	//Create 10 Items
	bool genItems = false;
    unsigned int item = 1;
    while (!genItems) {
        unsigned int Row = 2 + (rand() % (rows - 2));
        unsigned int Col = 2 + (rand() % (cols - 2));
        //randomly generating 10 items needs to be updated
        if (QueryLocation(Row, Col) == 0) {
            ItemLocation[Row][Col] = &Items[Row][Col];
            Items[Row][Col].setUpItem(1+(rand()%8));
            ++item;
            if (item == tenPercent) {
                genItems = true;
            }
        }
    }

}
//Used to find out wether an enemy,player or blank space is at each location
int FantasyGame::QueryLocation(unsigned int Row, unsigned int Col) {
    for (unsigned int i = 6; i < 16; ++i) {
        //if the location is an enemy reutrn 6-16 for enemies
        if (CharacterLocation[Row][Col] == &(Enemies[Row][Col])) {
            return 1;
        }
    }
	for (unsigned int j = 17; j < 27; ++j) {
		if (ItemLocation[Row][Col] == &(Items[Row][Col])) {
            return 2;
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

bool FantasyGame::LocateCharacter(unsigned int& rRow, unsigned int& cCol,unsigned int Rows,unsigned int Cols,character* xyCharacter) {
	for (unsigned int Row = 0; Row < Rows; ++Row) {
		for (unsigned int Col = 0; Col < Cols; ++Col) {
			if (CharacterLocation[Row][Col] == xyCharacter) {
				rRow = Row;
				cCol = Col;
				return true;
			}
		}
	}
	return false;
}

bool FantasyGame::checkItemType(unsigned int Row, unsigned int Col){
    if (Items[Row][Col].getType() == "Ring"){
        return true;
    }
    for (int j = 0;j<inventory.size(); ++j){
        if(inventory[j].getType() == Items[Row][Col].getType()){
            return false;
        }
    }
    return true;
}
bool FantasyGame::checkInventorySpace(unsigned int Row,unsigned int Col){
    unsigned int total = 0;
    for (int j = 0;j<inventory.size(); ++j){
        total = (total + inventory[j].getWeight());
    }
    if ((total + Items[Row][Col].getWeight())>Player.getStrength())
    {
        return false;
    }
    return true;
}

void FantasyGame::setUpItems(unsigned int Row, unsigned int Col)
{
    Player.setCharDefense(Player.getCharDefense() + Items[Row][Col].getDefense());
    Player.setCharAttack(Player.getCharAttack() + Items[Row][Col].getAttack());
    Player.setStrength(Player.getStrength() + Items[Row][Col].getStrength());
    Player.setbaseHealth(Player.getbaseHealth() + Items[Row][Col].getHealth());
}

void FantasyGame::removeItems(unsigned int Row, unsigned int Col)
{
    Player.setCharDefense(Player.getCharDefense() - Items[Row][Col].getDefense());
    Player.setCharAttack(Player.getCharAttack() - Items[Row][Col].getAttack());
    Player.setStrength(Player.getStrength() - Items[Row][Col].getStrength());
    Player.setbaseHealth(Player.getbaseHealth() - Items[Row][Col].getHealth());
}

void FantasyGame::NightDay()
{
    if (orcs.size() > 0){
        if(getNight() == false){
            for (int j = 0;j<orcs.size(); ++j){
                orcs[j] -> setCharAttack(orcs[j] -> getCharAttack() - 20);
                orcs[j] -> setCharDefense(orcs[j] -> getCharDefense() - 15);
                orcs[j] -> setchanceAttack(orcs[j] -> getchanceAttack() - 75);
                orcs[j] -> setchanceDefense(orcs[j] -> getchanceDefense() - 25);

            }
        }else if (getNight() == true){
            for (int j = 0;j<orcs.size(); ++j){
                orcs[j] -> setCharAttack(orcs[j] -> getCharAttack() + 20);
                orcs[j] -> setCharDefense(orcs[j] -> getCharDefense() + 15);
                orcs[j] -> setchanceAttack(orcs[j] -> getchanceAttack() + 75);
                orcs[j] -> setchanceDefense(orcs[j] -> getchanceDefense() + 25);
            }

        }
    }
}

void FantasyGame::lookAround(unsigned int Row,unsigned int Col)
{
    cout <<"Currently Standing on: " << Items[Row][Col].getname() << "\n";
    cout <<"North there is: " << Items[Row - 1][Col].getname() << Enemies[Row - 1][Col].getrace() << "\n";
    cout <<"South there is: " << Items[Row + 1][Col].getname() << Enemies[Row + 1][Col].getrace() << "\n";
    cout <<"West there is: " << Items[Row][Col - 1].getname() << Enemies[Row][Col - 1].getrace()  << "\n";
    cout <<"East there is: " << Items[Row][Col + 1].getname() << Enemies[Row][Col + 1].getrace()  << "\n";
}

void FantasyGame::showInventory()
{
	cout << "INVENTORY: \n";
	if (inventory.size() > 0){
		for (int j = 0;j<inventory.size(); ++j){
		   cout << j << "). " << inventory[j].getname() << ", Weight: " << inventory[j].getWeight() ;
		   cout<< ", Attack: " << inventory[j].getAttack()<< ", Defense: " << inventory[j].getDefense();
		   cout << ", Strength: " << inventory[j].getStrength()<<  ", Health: " << inventory[j].getHealth()<< "," << "\n";
		}
	}
	else{
		cout << "Nothing in inventory" << "\n";
	}
	cout << "Gold: " << Gold << "\n";


}

bool FantasyGame::pickUpItem(int CurLoc,int PlayerRow,int PlayerCol)
{
	if (CurLoc == 2){
		if(checkItemType(PlayerRow,PlayerCol) == true){
			if(checkInventorySpace(PlayerRow,PlayerCol) == true){
			inventory.push_back(Items[PlayerRow][PlayerCol]);
			setUpItems(PlayerRow,PlayerCol);
			ItemLocation[PlayerRow][PlayerCol] = 0;
			}else{
			  cout << "Not Strong enough to carry any more items \n";
			}
		}else{
			cout << "Item of Type: " << Items[PlayerRow][PlayerCol].getType() << " already present in inventory \n";
			return false;
		}
		return true;
   }
   else{
		return false;
   }

}

bool FantasyGame::dropItem(int CurLoc,int PlayerRow,int PlayerCol)
{
	if (inventory.size() > 0){
		cout << "INVENTORY: \n";
		for (int j = 0;j<inventory.size(); ++j){
           cout << j << "). " << inventory[j].getname() << ", Weight: " << inventory[j].getWeight() ;
           cout<< ", Attack: " << inventory[j].getAttack()<< ", Defense: " << inventory[j].getDefense();
           cout << ", Strength: " << inventory[j].getStrength()<<  ", Health: " << inventory[j].getHealth()<< "," << "\n";
		}
		if(CurLoc == 3){
			unsigned int x;
			cout << "Please enter Item number from inventory list: ";
			cin >> x;
			ItemLocation[PlayerRow][PlayerCol] = &Items[PlayerRow][PlayerCol];
			Items[PlayerRow][PlayerCol].setUpItem(inventory[x].getID());
			removeItems(PlayerRow,PlayerCol);
			inventory.erase(inventory.begin() + x);
			return true;
		}
		else{
			cout << "Unable to drop item as space is not free!";
			return false;
		}
	}
	else{
		cout << "Nothing Present in inventory";
		return false;
	}

}

bool FantasyGame::MovePlayer(const char Movement,unsigned int Rows,unsigned int Cols) {
	unsigned int PlayerRow;
	unsigned int PlayerCol;
	LocateCharacter(PlayerRow, PlayerCol, Rows, Cols, &Player);
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
        case 'L':
            {
                lookAround(PlayerRow,PlayerCol);
                break;
            }
        case 'P':
            {
				pickUpItem(CurLoc,PlayerRow,PlayerCol);
                break;
            }
        case 'O':
            {
				dropItem(CurLoc,PlayerRow,PlayerCol);
             	break;
            }
        case 'I':
            {
				showInventory();
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
	}else if (NextLoc == 2){ 
		CharacterLocation[NextRow][NextCol] = &Player;
		CharacterLocation[PlayerRow][PlayerCol] = 0;
		return true;
	}else if (NextLoc == 1) {
		Player.Attack(Enemies[NextRow][NextCol]);
        RemoveDeadFoes(NextRow,NextCol,Rows,Cols);
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
void FantasyGame::RemoveDeadFoes(unsigned int Row, unsigned int Col,unsigned int Rows,unsigned int Cols) {
    if (Enemies[Row][Col].IsDead()) {
        if (LocateCharacter(Row, Col,Rows,Cols,&(Enemies[Row][Col]))) {
            Gold = (Gold + Enemies[Row][Col].getCharDefense());
            CharacterLocation[Row][Col] = 0;
            std::cout << "Enemy Killed!" << std::endl;
        }
    }
}
//checks wether all foes are dead if so gameover
bool FantasyGame::AllFoesDead(unsigned int Rows, unsigned int Cols) {
	bool AllDead = true;
    for (int down = 0; down < Rows; down++) {
        for (int across = 0; across < Cols; across++) {
            switch(QueryLocation(down, across)){
                case 2: //End Game no enemies
                    AllDead = false;
                break;
            }
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
			case 2:  // item
				cout << "$";
			break;
			case 1: //Enemy
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
cout << "\n Health: " << Player.getbaseHealth() << "\n Attack: " << Player.getCharAttack() << "\n Defense: " << Player.getCharDefense() << "\n Strength: " << Player.getStrength();
}


