// Header file for the Character class
//
// Contains very basic board structure.
// authors: Hugh, Conor, Diarmuid
// date:    12.11.2016
//////////////////////////////////////////////////////////////////////
#ifndef CHARACTER_H
#define CHARACTER_H
 
using namespace std;

class character
{
public:
    //character class
    character();
    //player attacks an enemy
    //enemies can't attack as they can't move
    void Attack(character& enemy);
    //check if character is dead
    bool IsDead();

private:
    //attack chance
    unsigned int chanceAttack;
    //defense chance
    unsigned int chanceDefense;
    //health
    int baseHealth;
    //attack
    unsigned int CharAttack;
    //defense
    unsigned int CharDefense;
};
#endif 
