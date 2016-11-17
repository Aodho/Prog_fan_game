// Main Class
//
// The Main function is where execution of code takes palce
// authors: Hugh, Conor, Diarmuid
// date:    12.11.2016
//////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
//vector<vector<int> > map;
#include "board.h"
using namespace std;

int main()
{
	try{

    char move;
    int plrX = 1, plrY = 1; // player start point
    unsigned int Rows,Cols;
    cout << "Please enter the number of rows:";
    cin >> Rows;
    Rows = Rows + 2;
    cout << "Please enter the number of colunms:";
    cin >> Cols;
    Cols = Cols +2;
    board newBoard(Rows,Cols);
    do
    {
        newBoard.displayBoard(Rows,Cols);
        // read the move
        cout << "Enter a move using (W=up,A=left,S=down,D=Right):";
        cin >> move;
        move = toupper(move);

        switch (move)
        {
            // left
                case 'A' :
                    if (plrY > 1)   // if 1 we are against the wall.
                    {
                        if (board::map[plrX][plrY-1] == 0 || board::map[plrX][plrY-1] == 1 || board::map[plrX][plrY-1] == 2)
                        {
                            board::map[plrX][plrY] = 0;  // clear existing spot
                            board::map[plrX][plrY - 1] = 3; // new position.
                            plrY--;
                        }
                    }
                break;
                // right
                case 'D' :
                	if (plrY < Rows-1)   // if 9 we are against the wall.
                {
                    if (board::map[plrX][plrY + 1] == 0 || board::map[plrX][plrY+1] == 1 || board::map[plrX][plrY+1] == 2)
                    {
                        board::map[plrX][plrY] = 0;  // clear existing spot
                        board::map[plrX][plrY + 1] = 3; // new position.
                        plrY++;
                    }
                }
                break;
                // up
                case 'W' :
                    if (plrX > 1)   // if 1 we are against the wall.
                    {
                        if (board::map[plrX-1][plrY] == 0 || board::map[plrX-1][plrY] == 1 || board::map[plrX-1][plrY] == 2)
                        {
                            board::map[plrX][plrY] = 0;  // clear existing spot
                            board::map[plrX-1][plrY] = 3; // new position.
                            plrX--;
                        }
                    }
                break;
                // down
                case 'S' :
                    if (plrX < Cols-1)   // if 9 we are against the wall.
                    {
                        if (board::map[plrX + 1][plrY] == 0 || board::map[plrX+1][plrY] == 1 || board::map[plrX+1][plrY] == 2)
                        {
                            board::map[plrX][plrY] = 0;  // clear existing spot
                            board::map[plrX + 1][plrY] = 3; // new position.
                            plrX++;
                        }
                    }
                break;
        }

    } while (move != 'Q');
    return 0;

	}
	catch (const char *ex)
	{
		cout << "\n\nException detected:\n";
		cout << ex << endl;
  	}
  	catch (...)
  	{
    	cout << "\n\nUnknown exception detected:\n";
	}
}

