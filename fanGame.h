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
    bool MovePlayer(const char Movement);
    //print the board
    void PrintBoard(int rows, int cols);
    //check if the player is alive if not end game
    bool PlayerIsDead();
    //remove dead enemies from the board
    void RemoveDeadFoes();
    //end game if all foes dead
    bool AllFoesDead();
    static vector<item> inventory;
    bool checkItemType(unsigned int x);
    bool checkInventorySpace(unsigned int CurLoc);


private:
    //locate a character
    bool LocateCharacter(unsigned int& rRow, unsigned int& cCol, character* xyCharacter);


    //createa new board
    board newBoard(int rows, int cols);
    // create a player character
    character Player;
    //create enemy characters
    character Enemies[20];
    //charcter temp = character(1);
    //Enemies[0]= temp;

    // should use two d arrys to store both above and below
    //create items
    item Items[20];

    //create a matrix of character locations
    static vector<vector<character*> > CharacterLocation;
    //create a matrix of item locations
    static vector<vector<item*> > ItemLocation;
    //static map<int,item> pickedUpItems;
};

#endif

