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

class board
{
public:

//public matrix editable from anywhere in the program
static vector< vector<int> > map;

board(int rows,int cols);
//initialise board class

private:
int Rows;
int Cols;

};

#endif

