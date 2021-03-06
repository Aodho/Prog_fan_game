// Header file for the main fantasy game class
//
// Contains main functions of game.
// authors: Hugh, Conor, Diarmuid
// date:    12.11.2016
//////////////////////////////////////////////////////////////////////
#ifndef FANGAME_H
#define FANGAME_H

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
#include "board.h"
#include "character.h"
#include "item.h"
#include <map>
using namespace std;

class FantasyGame
{
public:
    //create a new game
    FantasyGame(int rows, int cols);
    //find out character or item location
    int QueryLocation(unsigned int Rows, unsigned int Cols);
    //Move the player around the board
    bool MovePlayer(const char Movement,unsigned int Rows,unsigned int Cols);
    //print the board
    void PrintBoard(int rows, int cols);
    //check if the player is alive if not end game
    bool PlayerIsDead();
    //remove dead enemies from the board
    void RemoveDeadFoes(unsigned int Row, unsigned int Col,unsigned int Rows,unsigned int Cols);
    //end game if all foes dead
    bool AllFoesDead(unsigned int Row, unsigned int Col);
    //Inventory of items
    static vector<item> inventory;
    //A list of the Orcson the board
    static vector<character*> orcs;
    //Function to check the type of the item
    bool checkItemType(unsigned int Row, unsigned int Col);
    //Function to check the strength of the character
    bool checkInventorySpace(unsigned int Row, unsigned int Col);
    //Function used to create Items on the board
    void setUpItems(unsigned int Row, unsigned int Col);
    //Function used to remove items from the board whe nthey are picked up
    void removeItems(unsigned int Row, unsigned int Col);
    //Function used to look at the tiles adjecent to the player and the current player tile
    void lookAround(unsigned int Row,unsigned int Col);
    //Function used to show the current inventory the player is holding
    void showInventory();
    //Used to allow the player to pick up an item and place it into their inventory
    bool pickUpItem(int CurLoc, int Row, int Col);
    //Used to allow the player to drop items back onto the board
    bool dropItem(int CurLoc, int Row, int Col);
    //Used to swap between night and day
    void NightDay();
    //Used to both get and set night
    bool getNight()
       {
         return night;
       }
    void setNight(bool n)
       {
         night = n;
       }


private:
    //locate a character
    bool LocateCharacter(unsigned int& rRow, unsigned int& cCol,unsigned int Rows,unsigned int Cols, character* xyCharacter);
    //True or false value for wether it is night or day
    bool night;
    //create a new board
    board newBoard(int rows, int cols);
    // create a player character
    character Player;
    //create enemy characters
    static std::vector<std::vector<character> > Enemies;
    //create items
    static std::vector<std::vector<item> > Items;
    //create a matrix of character locations
    static vector<vector<character*> > CharacterLocation;
    //create a matrix of item locations
    static vector<vector<item*> > ItemLocation;
    //static map<int,item> pickedUpItems;
};

#endif

