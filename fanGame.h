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
using namespace std;

class FantasyGame
{
public:

    FantasyGame(int rows, int cols);

    int QueryLocation(unsigned int Rows, unsigned int Cols);

    bool MovePlayer(const char Movement);

    void PrintBoard(int rows, int cols);

    bool PlayerIsDead();

    void RemoveDeadFoes();

    bool AllFoesDead();

private:
    bool LocateCharacter(unsigned int& rRow, unsigned int& cCol, character* xyCharacter);
    board newBoard(int rows, int cols);
    character Player;
    character Enemies[20];
    static vector<vector<character*> > CharacterLocation;
};

#endif

