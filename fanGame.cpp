// FantasyGame class, used for a lot of the main game functions
//
// Contains Most of the heavy lifting for the program including:
// Player Attribute mulipulation , Movement/action functions, Player/Enemy/Item generation,
//
// authors: Hugh, Conor, Diarmuid
// date:    12.11.2016
//////////////////////////////////////////////////////////////////////

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

vector< vector<character*> > FantasyGame::CharacterLocation(10,vector<character*>(10)); //initialise a matrix of character pointers showing locations

vector< vector<item*> > FantasyGame::ItemLocation(10,vector<item*>(10)); //initialise a matrix of item pointers showing locations

vector<item> FantasyGame::inventory(0); //initialise the inventory

vector<character*> FantasyGame::orcs(0);//initialise a list of pointer to orcs on the board

vector< vector<item> > FantasyGame::Items(10,vector<item>(10));//Initialise a matrix of Items

vector< vector<character> > FantasyGame::Enemies(10,vector<character>(10));//Initialise a matix of Enemies

unsigned int Gold = 0;//Player Gold counter

/*FantasyGame(int rows,int cols)
 *
 *Used to generate all the characters and Items present on the board
 */
FantasyGame::FantasyGame(int rows,int cols) {

    // a selection process for the user to chose a race

    int p = 0;
    while(p<1 || p>5){		//While loop to ensure the user chooses a number between 1 and 5
    cout << "Please choose a race.\n" << "Select the corresponding number:\n" <<
            "1 For HUMAN\n2 For ELF\n3 For DWARF\n4 For HOBBIT\n5 for Orc\n"  <<endl;
    cin >> p;
    }
    cout << "Good Choice Young Padawan! You Have Chosen: " << p << endl;


	// Initlialize the random number generator
    time_t qTime;
    time(&qTime);
    setNight(false);
    srand((unsigned int)qTime);
    int squares = rows*cols;
    int tenPercent = (double)squares/(double)10; // * (1/10)
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
	while (!startPos) {//boolean while loop - while startposition is false
		unsigned int Row = 1;
		unsigned int Col = 1;
		if (QueryLocation(Row, Col) == 0) { // check position (1,1), is it empty? if it is, start position = true and put Player there.
			startPos = true;
            //setting up the player a point (1,1) in the matrix
			CharacterLocation[Row][Col] = &Player;
			Player.setUpCharacter(p);
            if (p == 5){
               orcs.push_back(&Player);
            }

		}
	}
	// Create 10%ofBoard Enemies
     bool startPos2 = false;
     unsigned int foe = 1;
	while (!startPos2) {
		unsigned int Row = 2 + (rand() % (rows - 2)); //randomly select row and collumn points
		unsigned int Col = 2 + (rand() % (cols - 2));
        //randomly generating enemies
		if (QueryLocation(Row, Col) == 0) { //if these points are empty insert enemies
            		int x = 1+(rand()%5); //randomly select races for the enemies to be
			CharacterLocation[Row][Col] = &Enemies[Row][Col];
			Enemies[Row][Col].setUpCharacter(x);
	        if (x == 5){
	   		orcs.push_back(&Enemies[Row][Col]);
	    		}
			++foe; //for every enemy add 1 to int foe, when foe = 10% of number of squares, Stop i.e start position 2 = true
		if (foe == tenPercent) {
				startPos2 = true;
			}
	    }
	}
	//Create 10%ofborad Items - follows the same format as above
	bool genItems = false;
	unsigned int item = 1;
	while (!genItems) {
		unsigned int Row = 2 + (rand() % (rows - 2)); //randomly selects row and collumn points
		unsigned int Col = 2 + (rand() % (cols - 2));
		//randomly generating items needs
		if (QueryLocation(Row, Col) == 0) { 
		    ItemLocation[Row][Col] = &Items[Row][Col];
		    Items[Row][Col].setUpItem(1+(rand()%8)); //use random numbers
		    ++item;
		    if (item == tenPercent) { //when 10% of the squares are filled with items, stop.
		        genItems = true;
		    }
		}
	}

}

/*QueryLocation(unsigned int Row, unsigned int Col)
 *
 *Used to find out wether an enemy,player or blank space is at each location
 */
int FantasyGame::QueryLocation(unsigned int Row, unsigned int Col) {

    //if the location contains an enemy return 1
    if (CharacterLocation[Row][Col] == &(Enemies[Row][Col])) {
        return 1;
       }
	//if the location contains an item return 2
    if (ItemLocation[Row][Col] == &(Items[Row][Col])) {
        return 2;
        }
    //if player location return 3
	if (CharacterLocation[Row][Col] == &Player) {
     	    return 3;
    	//else return the board value wall(5) or empty space(0)
    }
    else {//if it does contin player,enemy or item.
        //return the base board containing blank spaces and walls
	    return board::map[Row][Col];
   	}
}

/*LocateCharacter(unsigned int& rRow, unsigned int& cCol,unsigned int Rows,unsigned int Cols,character* xyCharacter)
 *
 *Used to find a particualr character on the board when the character is found will return true and postion
 */
bool FantasyGame::LocateCharacter(unsigned int& rRow, unsigned int& cCol,unsigned int Rows,unsigned int Cols,character* xyCharacter) {
	for (unsigned int Row = 0; Row < Rows; ++Row) { //check through the rows
		for (unsigned int Col = 0; Col < Cols; ++Col) { //check through collumns
			if (CharacterLocation[Row][Col] == xyCharacter) {
				rRow = Row;//Used to return row of character
				cCol = Col;//used to return column of character
				return true;// return true when found
			}
		}
	}
	return false;
}

/*checkItemType(unsigned int Row, unsigned int Col)
 *
 * Checks the type of Item to determine wether or not it can be picked up
 */
bool FantasyGame::checkItemType(unsigned int Row, unsigned int Col){ //check item type, funcion used in pickupitem function
	if (Items[Row][Col].getType() == "Ring"){
		return true; //rings are ok to have more than one of
	}

	for (int j = 0;j<inventory.size(); ++j){
		if(inventory[j].getType() == Items[Row][Col].getType()){ //only allowed one of each other type
		    return false;
		}
	}
	    return true;
}

/*checkInventorySpace(unsigned int Row,unsigned int Col)
 *
 * Used to check wether or not the player will be overencumbered by picking up the next item
 */
bool FantasyGame::checkInventorySpace(unsigned int Row,unsigned int Col){
	unsigned int total = 0;

	for (int j = 0;j<inventory.size(); ++j){
		total = (total + inventory[j].getWeight());
	}

	if ((total + Items[Row][Col].getWeight())>Player.getStrength()) //if total weight  of inventory + new item weight is more than players stength then it is too big
	{
		return false;
	}
	return true;
}

/*setUpItems(unsigned int Row, unsigned int Col)
 *
 *Updates player attributes bassed on items in inventory
 */
void FantasyGame::setUpItems(unsigned int Row, unsigned int Col){
    //using the setters in the character.h file, with the character and item getters
	Player.setCharDefense(Player.getCharDefense() + Items[Row][Col].getDefense()); 
	Player.setCharAttack(Player.getCharAttack() + Items[Row][Col].getAttack());
	Player.setStrength(Player.getStrength() + Items[Row][Col].getStrength());
	Player.setbaseHealth(Player.getbaseHealth() + Items[Row][Col].getHealth());
}

/*removeItems(unsigned int Row, unsigned int Col)
 *
 *Updates player attributes bassed on items removed from inventory
 */
void FantasyGame::removeItems(unsigned int Row, unsigned int Col)
{
	//same as above, just in reverse, deducts the attributes
	Player.setCharDefense(Player.getCharDefense() - Items[Row][Col].getDefense());
	Player.setCharAttack(Player.getCharAttack() - Items[Row][Col].getAttack());
	Player.setStrength(Player.getStrength() - Items[Row][Col].getStrength());
	Player.setbaseHealth(Player.getbaseHealth() - Items[Row][Col].getHealth());
}

/*NightDay()
 *
 *changes the orcs attributes according to day/night (every 5 moves)
 */
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

/*lookAround(unsigned int Row,unsigned int Col)
 *
 *tells the user what is around them by describing what is in their current location
 *And in those locations adjectent to them.
 */
void FantasyGame::lookAround(unsigned int Row,unsigned int Col)
{
	cout <<"Currently Standing on: " << Items[Row][Col].getname() << "\n";
	cout <<"North there is: " << Items[Row - 1][Col].getname() << Enemies[Row - 1][Col].getrace() << "\n";
	cout <<"South there is: " << Items[Row + 1][Col].getname() << Enemies[Row + 1][Col].getrace() << "\n";
	cout <<"West there is: " << Items[Row][Col - 1].getname() << Enemies[Row][Col - 1].getrace()  << "\n";
	cout <<"East there is: " << Items[Row][Col + 1].getname() << Enemies[Row][Col + 1].getrace()  << "\n";
}

/*showInventory()
 *
 *Shows what is curently present in the player inventory
 */
void FantasyGame::showInventory()
{
	cout << "INVENTORY: \n";
	if (inventory.size() > 0){
		for (int j = 0;j<inventory.size(); ++j){ //lists them from 0 up
		   cout << j << "). " << inventory[j].getname() << ", Weight: " << inventory[j].getWeight() ;
		   cout<< ", Attack: " << inventory[j].getAttack()<< ", Defense: " << inventory[j].getDefense();
		   cout << ", Strength: " << inventory[j].getStrength()<<  ", Health: " << inventory[j].getHealth()<< "," << "\n";
		} //it lists the attributes and there names
	}
	else{
		cout << "Nothing in inventory" << "\n";
	}
	cout << "Gold: " << Gold << "\n";


}

/*pickUpItem(int CurLoc,int PlayerRow,int PlayerCol)
 *
 * adds items to the inventory if there is space and Item complies with type rules
 */
bool FantasyGame::pickUpItem(int CurLoc,int PlayerRow,int PlayerCol)
{
	if (CurLoc == 2){
		if(checkItemType(PlayerRow,PlayerCol) == true){ //checks the type of the item is ok
			if(checkInventorySpace(PlayerRow,PlayerCol) == true){ //use checkinventoryspace function to make sure player can pickup
			inventory.push_back(Items[PlayerRow][PlayerCol]);//adds Item to inventory
			setUpItems(PlayerRow,PlayerCol);//updates player attributes based on item
			ItemLocation[PlayerRow][PlayerCol] = 0;//removes item from board
			}else{
			  cout << "Not Strong enough to carry any more items \n";
			}
		}else{
			cout << "Item of Type: " << Items[PlayerRow][PlayerCol].getType() << " already present in inventory \n"; //if item type already exists, cant pick up.
			return false;
		}
		return true;
  	}
   	else{
		return false;
   	}

}

/*dropItem(int CurLoc,int PlayerRow,int PlayerCol)
 *
 * Removes item from inventory if there is free space and drops it on the board
 */
bool FantasyGame::dropItem(int CurLoc,int PlayerRow,int PlayerCol)
{
	if (inventory.size() > 0){
		cout << "INVENTORY: \n"; // shows inventory
		for (int j = 0;j<inventory.size(); ++j){
           cout << j << "). " << inventory[j].getname() << ", Weight: " << inventory[j].getWeight() ;
           cout<< ", Attack: " << inventory[j].getAttack()<< ", Defense: " << inventory[j].getDefense();
           cout << ", Strength: " << inventory[j].getStrength()<<  ", Health: " << inventory[j].getHealth()<< "," << "\n";
		}
		if(CurLoc == 3){ //checks the space is empty
			unsigned int x;
			cout << "Please enter Item number from inventory list: "; //player selects item from list that they would like to drop
			cin >> x;
			ItemLocation[PlayerRow][PlayerCol] = &Items[PlayerRow][PlayerCol];//Places item on board
			Items[PlayerRow][PlayerCol].setUpItem(inventory[x].getID());//Sets up the itme on board
			removeItems(PlayerRow,PlayerCol);//removes Item attribtes to player
			inventory.erase(inventory.begin() + x);//removes Item from inventory
			return true;
		}
		else{
			cout << "Unable to drop item as space is not free!";
			return false; //if space isn't empt, can't drop item
		}
	}
	else{
		cout << "Nothing Present in inventory"; //if there is nothing in the inventory, can't drop item
		return false;
	}

}

/*MovePlayer(const char Movement,unsigned int Rows,unsigned int Cols)
 *
 * Used to move the player and complete actions such as look,pick up item,drop item and show inventory.
 */
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
		//sets up the buttons for other commands - other functions in this class
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
        bool night = getNight();
		Player.Attack(Enemies[NextRow][NextCol],night);
        RemoveDeadFoes(NextRow,NextCol,Rows,Cols);
		return true;
     	//if not enemy or player returns false as it is a wall
	} else {
		return false;
	}
}

/*PlayerIsDead()
 *
 * checks if player is dead
 */
bool FantasyGame::PlayerIsDead() {
	return Player.IsDead();
}

/*RemoveDeadFoes(unsigned int Row, unsigned int Col,unsigned int Rows,unsigned int Cols)
 *
 * removes dead enemies from the board and adds gold to the player based on their defense
 */
void FantasyGame::RemoveDeadFoes(unsigned int Row, unsigned int Col,unsigned int Rows,unsigned int Cols) {
    if (Enemies[Row][Col].IsDead()) {
        if (LocateCharacter(Row, Col,Rows,Cols,&(Enemies[Row][Col]))) {
            Gold = (Gold + Enemies[Row][Col].getCharDefense());
            CharacterLocation[Row][Col] = 0;
            std::cout << "Enemy Killed!" << std::endl;
        }
    }
}

/*AllFoesDead(unsigned int Rows, unsigned int Cols) 
 *
 *checks wether all foes are dead if so gameover
 *This is done by querying the board for instances of enemies
 *If an enemy(2) is found returns false as enemy is still present on board
 */
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

/*PrintBoard(int Rows,int Cols) 
 *
 * simple loop to display board
 * swap numbers out with symbols
 */
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
//prints out player stats
cout << "\n Health: " << Player.getbaseHealth() << "\n Attack: " << Player.getCharAttack() << "\n Defense: " << Player.getCharDefense() << "\n Strength: " << Player.getStrength();
}


