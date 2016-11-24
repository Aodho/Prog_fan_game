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
#include "board.h"
#include "fanGame.h"
#include "character.h"
using namespace std;

int main()
{
	try{
    char move;
    unsigned int Rows,Cols;

    //takes in number of rows of the board
    cout << "Please enter the number of rows:";
    cin >> Rows;
    Rows = Rows + 2;

    //takes in the number of colums of the board
    cout << "Please enter the number of colunms:";
    cin >> Cols;
    Cols = Cols +2;

    //generates the game and board
    FantasyGame newFantasyGame(Rows,Cols);
    system("clear");
    
    //sets the gameover to be false
	bool GameOver = false;
    do
    {
        // read the move
        newFantasyGame.PrintBoard(Rows,Cols);
        cout << "Enter a move using (W=up,A=left,S=down,D=Right)\n";
        cout << "Other actions(P=pick up item, I = check inventory, O = Drop Item, Q = Quit Game):";
        cin >> move;
        move = toupper(move);

        system("clear");
        if(newFantasyGame.MovePlayer(move)){
            //If the Player is dead
            if(newFantasyGame.PlayerIsDead()){
               cout << "You have Died!" << endl;
               GameOver = true;
            } else {
                // Remove all dead Foes from game
                newFantasyGame.RemoveDeadFoes(Rows,Cols);
                // If all of the Foes are dead
                if (newFantasyGame.AllFoesDead(Rows,Cols)) {
                    cout << "Map Clear!" << endl;
                    GameOver = true;
                }
            }
        }
    } while (!GameOver && move != 'Q');
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

