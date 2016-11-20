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
    character();

    void Attack(character& enemy);

    bool IsDead();

private:
    unsigned int chanceAttack;
    unsigned int chanceDefense;
    int baseHealth;
    unsigned int CharAttack;
    unsigned int CharDefense;
};
#endif 
