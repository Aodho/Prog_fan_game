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
    //Char used to detmine player action using a switch
    char move;
    //ints used to take in the desired size of board
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

    //Counter used to determine the number of turns
    int counter = 0;
    //Set the night to be false to start in the day
    bool night =false;

    //sets the gameover to be false
    bool GameOver = false;
    do
    {
        // read the move
        newFantasyGame.PrintBoard(Rows,Cols); //explain controls
        cout << "\n\nEnter a move using (W=up,A=left,S=down,D=Right)\n";
        cout << "Other actions(P=pick up item,L = Look Around, I = check inventory, O = Drop Item, Q = Quit Game):";
        cin >> move;
        //Converts move to upper case for switch statement
        move = toupper(move);

        system("clear");
        counter++; //increment counter for orc day/night
        if(newFantasyGame.getNight() == false){
            if(counter==5){//if 5 turns have passed
                newFantasyGame.setNight(true);//change night after 5 turns
                newFantasyGame.NightDay();//used to update the orcs attributes
                cout << "It is now NightTime Orcs are stronger \n\n";
                counter =0;//reset the counter
            }
        }
        else if(newFantasyGame.getNight() == true){
            if(counter==5){//if 5 turns have passed
                newFantasyGame.setNight(false);//change to day after 5 turns
                newFantasyGame.NightDay();//used to update the orcs attributes
                cout << "It is now DayTime Orcs are weaker \n\n";
                counter = 0;//reset the counter
            }
        }

        if(newFantasyGame.MovePlayer(move,Rows,Cols)){
            //If the Player is dead
            if(newFantasyGame.PlayerIsDead()){//function determines if the player is alive
               cout << "You have Died!" << endl;
               GameOver = true;//if player is dead set gameover to be true and breakout of while loop
            } else {
                // If all of the Foes are dead
                if (newFantasyGame.AllFoesDead(Rows,Cols)) {//function determines if there are any enemies left on the board
                    cout << "Map Clear!" << endl;
                    GameOver = true;//if all enemies are dead set gameover to be true and breakout of while loop
                }
            }
        }
    } while (!GameOver && move != 'Q');//Breakout of while loop if gameover is true or "q" is entered
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

