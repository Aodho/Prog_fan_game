// Header file for the Character class
//
// Contains very basic board structure.
// authors: Hugh, Conor, Diarmuid
// date:    12.11.2016
//////////////////////////////////////////////////////////////////////
#include "fanGame.h"
#ifndef CHARACTER_H
#define CHARACTER_H
 
using namespace std;

class character
{
public:
    //character class
    character();
    //initialise with Id
        character(int i)
        {
            id = i;
        }
/*A series of getter and setter methods for 
 * a variety of attributes including:
 * ID,race,Attack,Defence,AttackChance,DefenseChance,Strength and health
 */
        int getID()
        {
            return id;
        }
        string getrace()
        {
             return race;
        }

        int getchanceAttack()
        {
            return chanceAttack;
        }

        int getchanceDefense()
        {
            return chanceDefense;
        }

        int getCharAttack()
        {
            return CharAttack;
        }

        int getCharDefense()
        {
            return CharDefense;
        }

        int getStrength()
        {
            return strength;
        }
    int getbaseHealth()
        {
            return baseHealth;
        }

    void setrace(string r)
        {
             race = r;
        }

        void setchanceAttack(int cA)
        {
             chanceAttack = cA;
        }

        void setchanceDefense(int cD)
        {
            chanceDefense = cD;
        }

        void setCharAttack(int A)
        {
            CharAttack = A;
        }

        void setCharDefense(int D)
        {
            CharDefense = D;
        }

        void setStrength(int S)
        {
            strength = S;
        }
    void setbaseHealth(int H)
        {
            baseHealth = H;
        }
/*setUpCharacter(int i)
 * Setting up the different character races
 * Uses setter methods to set the value of each race
 */
    void setUpCharacter(int i)
    {
        if(i==1){
        setrace("Human");
        setchanceAttack(66);
        setchanceDefense(50);
        setCharAttack(30);
        setCharDefense(20);
        setStrength(100);
        setbaseHealth(60);
        }
        if(i==2){
        setrace("Elf");
        setchanceAttack(100);
        setchanceDefense(25);
        setCharAttack(40);
        setCharDefense(10);
        setStrength(70);
        setbaseHealth(40);
        }
        if(i==3){
        setrace("Dwarf");
        setchanceAttack(66);
        setchanceDefense(66);
        setCharAttack(30);
        setCharDefense(20);
        setStrength(130);
        setbaseHealth(50);
        }
        if(i==4){
        setrace("Hobbit");
        setchanceAttack(33);
        setchanceDefense(66);
        setCharAttack(25);
        setCharDefense(20);
        setStrength(85);
        setbaseHealth(70);
        }
        if(i==5){
        setrace("Orc");
        setchanceAttack(25);
        setchanceDefense(25);
        setCharAttack(25);
        setCharDefense(10);
        setStrength(130);
        setbaseHealth(50);
        }
    }

    //player attacks an enemy
    //enemies can't attack as they can't move
    void Attack(character& enemy, bool night);
    //check if character is dead
    bool IsDead();
    //Function for special ability
    void Ability(character,bool,int);

private:
    //id
    unsigned int id;
    //race of character
    string race;
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
