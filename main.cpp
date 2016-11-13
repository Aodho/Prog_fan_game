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
using namespace std;

int main()
{
	try{

    char move;
    int plrX = 1, plrY = 1; // player start point
    unsigned int Rows,Cols;
    cout << "Please enter the number of rows:";
    cin >> Rows;
    cout << "Please enter the number of colunms:";
    cin >> Cols;
    Rows = Rows + 2;
    Cols = Cols + 2;

    int map[Rows][Cols];
    memset(map, 0, sizeof(map[0][0]) * Rows * Cols);
    for (int i = 0; i < Rows; i++){
        for (int j = 0; j < Cols; j++){
            int value = (rand() % 3);
            cout <<"value is :" <<value <<"\n\n";
            map[i][j] = value;
        };
    };
    for (int i = 0; i < Rows; i++){
         map[i][0] = 5;
         map[i][Cols-1] = 5;
        };
    for (int j = 0; j < Cols; j++){
         map[0][j] = 5;
         map[Rows-1][j] = 5;
        };
    map[1][1] = 3;
    do
    {
        system("clear");
        // display the map, just a simple loop
        for (int down = 0; down < Rows; down++) {
            for (int across = 0; across < Cols; across++) {
                switch (map[down][across])
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

        // read the move
        cout << "Enter a move:";
        cin >> move;
        move = toupper(move);

        switch (move)
        {
            // left
                case 'A' :
                    if (plrY > 1)   // if 1 we are against the wall.
                    {
                        if (map[plrX][plrY-1] == 0 || map[plrX][plrY-1] == 1 || map[plrX][plrY-1] == 2)
                        {
                            map[plrX][plrY] = 0;  // clear existing spot
                            map[plrX][plrY - 1] = 3; // new position.
                            plrY--;
                        }
                    }
                break;
                // right
                case 'D' :
                	if (plrY < Rows-1)   // if 9 we are against the wall.
                {
                    if (map[plrX][plrY + 1] == 0 || map[plrX][plrY+1] == 1 || map[plrX][plrY+1] == 2)
                    {
                        map[plrX][plrY] = 0;  // clear existing spot
                        map[plrX][plrY + 1] = 3; // new position.
                        plrY++;
                    }
                }
                break;
                // up
                case 'W' :
                    if (plrX > 1)   // if 1 we are against the wall.
                    {
                        if (map[plrX-1][plrY] == 0 || map[plrX-1][plrY] == 1 || map[plrX-1][plrY] == 2)
                        {
                            map[plrX][plrY] = 0;  // clear existing spot
                            map[plrX-1][plrY] = 3; // new position.
                            plrX--;
                        }
                    }
                break;
                // down
                case 'S' :
                    if (plrX < Cols-1)   // if 9 we are against the wall.
                    {
                        if (map[plrX + 1][plrY] == 0 || map[plrX][plrY+1] == 1 || map[plrX][plrY+1] == 2)
                        {
                            map[plrX][plrY] = 0;  // clear existing spot
                            map[plrX + 1][plrY] = 3; // new position.
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

