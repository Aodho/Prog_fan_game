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
//used to generate a matrix
vector< vector<int> > board::map(10,vector<int>(10));

board::board(int Rows, int Cols)
{
    map.resize(Rows);
    for (int i = 0; i < Rows; i++){
        map[i].resize(Cols);
        for (int j = 0; j < Cols; j++){
            int value = (rand() % 3);
            // add in random values between 0-2.
            // 0 for empty space, 1 for enemy, and 2 for item
            map[i][j] = value;
        };
    };

    for (int i = 0; i < Rows; i++){
         map[i][0] = 5;
         //add in 5 for walls to both sides of the matrix
         map[i][Cols-1] = 5;
        };

    for (int j = 0; j < Cols; j++){
         map[0][j] = 5;
         //add in 5 for walls to top and bottum of matrix
         map[Rows-1][j] = 5;
        };
    map[1][1] = 3;
    //add in player at postiton (1,1)
}

void board::displayBoard(int Rows, int Cols)
{
	system("clear");
	// display the map, just a simple loop
	for (int down = 0; down < Rows; down++) {
		for (int across = 0; across < Cols; across++) {
			switch (board::map[down][across])
			{
				case 0:  // Nothing
					cout << "X";
				break;
				case 1:  // item
					cout << "$";
				break;
				case 2: //Enemy
					cout << "£";
				break;
				case 3: //player
					cout << "@";
				break;
				case 5:  // wall
					cout << "#";
				break;
			}
		}
		cout << endl;
	}
}
