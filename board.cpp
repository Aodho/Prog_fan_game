// Definition of the board class
//
// Contains very basic board structure.
// authors: Hugh, Conor, Diarmuid
// date:    12.11.2016
//////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
#include "board.h"
using namespace std;

//vector< vector<int> > map;
//used to initialise a blank empty 10x10 matrix
vector< vector<int> > board::map(10,vector<int>(10));

board::board(int Rows, int Cols)
{
    //used to resize the initialised matrix to the correct number of rows
    map.resize(Rows);
    for (int i = 0; i < Rows; i++){
        //used to resize the initialised matrix to the correct number of colunms
        map[i].resize(Cols);
        for (int j = 0; j < Cols; j++){
            int value = 0;
            // setting all values in the matrix to 0 as 0 is empty space
            map[i][j] = value;
        };
    };

    for (int i = 0; i < Rows; i++){
         map[i][0] = 5;
         //add in 5 for walls to both left and right side of the matrix
         map[i][Cols-1] = 5;
        };

    for (int j = 0; j < Cols; j++){
         map[0][j] = 5;
         //add in 5 for walls to top and bottum of matrix
         map[Rows-1][j] = 5;
        };
}
