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
                        if (map[plrX][plrY-1] == 0)
                        {
                            map[plrX][plrY] = 0;  // clear existing spot
                            map[plrX][plrY - 1] = 3; // new position.
                            plrY--;
                        }
                        else if(map[plrX][plrY-1] == 1)
                        {
                            char item;
                            cout << "There is an item on the ground would you like to pick it up? Y/N";
                            cin >> item;
                            item = toupper(item);
                            switch(item){
                                case 'Y':
                                    cout << "you picked up an item";
                                    map[plrX][plrY] = 0;  // clear existing spot
                                    map[plrX][plrY-1] = 0;  // clear enemy spot
                                    map[plrX][plrY-1] = 3; //new position.
                                    plrY--;
                                    break;
                                case 'N':
                                    map[plrX][plrY] = 0;  // clear existing spot
                                    map[plrX][plrY-1] = 3; //new position.
                                    plrY--;
                                    break;
                            }
                        }
                        else if(map[plrX][plrY-1] == 2)
                        {
                          char fight;
                          cout << "There is an enemy ahead would you like to fight it? Y/N";
                          cin >> fight;
                          fight = toupper(fight);
                          switch(fight){
                              case 'Y':
                                  char win;
                                  cout << "Debug did you win? Y/N";
                                  cin >> win;
                                  win = toupper(win);
                                  if(win = 'Y'){
                                         map[plrX][plrY] = 0;  // clear existing spot
                                         map[plrX][plrY - 1] = 0;  // clear enemy spot
                                         map[plrX][plrY - 1] = 3; //new position.
                                         plrY--;
                                  }
                                  break;
                             case 'N':
                                  break;
                          }
                        }
                    }
                break;
                // right
                case 'D' :
                	if (plrY < Rows-1)   // if 9 we are against the wall.
                {
                    if (map[plrX][plrY + 1] == 0)
                    {
                        map[plrX][plrY] = 0;  // clear existing spot
                        map[plrX][plrY + 1] = 3; // new position.
                        plrY++;
                    }
                        else if(map[plrX][plrY+1] == 1)
                        {
                            char item;
                            cout << "There is an item on the ground would you like to pick it up? Y/N";
                            cin >> item;
                            item = toupper(item);
                            switch(item){
                                case 'Y':
                                    cout << "you picked up an item";
                                    map[plrX][plrY] = 0;  // clear existing spot
                                    map[plrX][plrY+1] = 0;  // clear enemy spot
                                    map[plrX][plrY+1] = 3; //new position.
                                    plrY++;
                                    break;
                                case 'N':
                                    map[plrX][plrY] = 0;  // clear existing spot
                                    map[plrX][plrY+1] = 3; //new position.
                                    plrY++;
                                    break;
                            }
                        }
                        else if(map[plrX][plrY+1] == 2)
                        {
                          char fight;
                          cout << "There is an enemy ahead would you like to fight it? Y/N";
                          cin >> fight;
                          fight = toupper(fight);
                          switch(fight){
                              case 'Y':
                                  char win;
                                  cout << "Debug did you win? Y/N";
                                  cin >> win;
                                  win = toupper(win);
                                  if(win = 'Y'){
                                         map[plrX][plrY] = 0;  // clear existing spot
                                         map[plrX][plrY + 1] = 0;  // clear enemy spot
                                         map[plrX][plrY + 1] = 3; //new position.
                                         plrY++;
                                  }
                                  break;
                             case 'N':
                                  break;
                          }
                        }
                }
                break;
                // up
                case 'W' :
                    if (plrX > 1)   // if 1 we are against the wall.
                    {
                        if (map[plrX-1][plrY] == 0)
                        {
                            map[plrX][plrY] = 0;  // clear existing spot
                            map[plrX-1][plrY] = 3; // new position.
                            plrX--;
                        }
                        else if(map[plrX-1][plrY] == 1)
                        {
                            char item;
                            cout << "There is an item on the ground would you like to pick it up? Y/N";
                            cin >> item;
                            item = toupper(item);
                            switch(item){
                                case 'Y':
                                    cout << "you picked up an item";
                                    map[plrX][plrY] = 0;  // clear existing spot
                                    map[plrX-1][plrY] = 0;  // clear enemy spot
                                    map[plrX-1][plrY] = 3; //new position.
                                    plrX--;
                                    break;
                                case 'N':
                                    map[plrX-1][plrY] = 0;  // clear existing spot
                                    map[plrX-1][plrY] = 3; //new position.
                                    plrX--;
                                    break;
                            }
                        }
                        else if(map[plrX-1][plrY] == 2)
                        {
                          char fight;
                          cout << "There is an enemy ahead would you like to fight it? Y/N";
                          cin >> fight;
                          fight = toupper(fight);
                          switch(fight){
                              case 'Y':
                                  char win;
                                  cout << "Debug did you win? Y/N";
                                  cin >> win;
                                  win = toupper(win);
                                  if(win = 'Y'){
                                         map[plrX][plrY] = 0;  // clear existing spot
                                         map[plrX -1][plrY] = 0;  // clear enemy spot
                                         map[plrX -1][plrY] = 3; //new position.
                                         plrX--;
                                  }
                                  break;
                             case 'N':
                                  break;
                          }
                        }
                    }
                break;
                // down
                case 'S' :
                    if (plrX < Cols-1)   // if 9 we are against the wall.
                    {
                        if (map[plrX + 1][plrY] == 0)
                        {
                            map[plrX][plrY] = 0;  // clear existing spot
                            map[plrX + 1][plrY] = 3; // new position.
                            plrX++;
                        }
                        else if(map[plrX+1][plrY] == 1)
                        {
                            char item;
                            cout << "There is an item on the ground would you like to pick it up? Y/N";
                            cin >> item;
                            item = toupper(item);
							switch(item){
							    case 'Y':
									cout << "you picked up an item";
                                    map[plrX][plrY] = 0;  // clear existing spot
									map[plrX+1][plrY] = 0;  // clear enemy spot
                                    map[plrX+1][plrY] = 3; //new position.
                                    plrX++;
									break;
								case 'N':
                                    map[plrX][plrY] = 0;  // clear existing spot
                                    map[plrX+1][plrY] = 3; //new position.
                                    plrX++;
									break;
							}
                        }
                        else if(map[plrX+1][plrY] == 2)
                        {
                          char fight;
                          cout << "There is an enemy ahead would you like to fight it? Y/N";
                          cin >> fight;
                          fight = toupper(fight);
                          switch(fight){
                              case 'Y':
                                  char win;
                                  cout << "Debug did you win? Y/N";
                                  cin >> win;
                                  win = toupper(win);
                                  if(win = 'Y'){
                                         map[plrX][plrY] = 0;  // clear existing spot
                                         map[plrX+1][plrY] = 0;  // clear enemy spot
                                         map[plrX+1][plrY] = 3; //new position.
                                         plrX++;
                                  }
                                  break;
                             case 'N':
                                  break;
                          }
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

