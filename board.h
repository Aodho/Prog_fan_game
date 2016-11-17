// Header file for the board class
//
// Contains very basic board structure.
// authors: Hugh, Conor, Diarmuid
// date:    12.11.2016
//////////////////////////////////////////////////////////////////////
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "board.h"
using namespace std;

//extern vector< vector<int> > map;
//initialize external vector of vectors map

class board
{
public:

static vector< vector<int> > map;

board(int rows,int cols);
//initialise board class
void displayBoard(int rows, int cols);

private:
int Rows;
int Cols;

};

#endif

