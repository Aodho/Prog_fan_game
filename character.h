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
	int getStrength()
	{   
		return strength;
	}

	void setStrength(int s)
	{
		strength =s;
	}

/*    character(int r)
    {
    race =r;

    }
void creat_other_feature(int r)
    {
        if(r==1)
        {
            setattack(37);
            setdefence(56);


        }
        if(r==2)
        {


        }

    }

    void setattack(int a1)
    {
        chanceAttack = a1;
    }
void setdefence(int a2)
{

    chanceDefence = a2;
}*/

    //player attacks an enemy
    //enemies can't attack as they can't move
    void Attack(character& enemy);
    //check if character is dead
    bool IsDead();

private:
    unsigned int race;
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
    //strength
    unsigned int strength;
};
#endif 
