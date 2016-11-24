#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
#include "character.h"
#include "fanGame.h"
using namespace std;

/*character()
 *  setting up the default character object.
 *  setting default values for attackChance, DefenseChance, 
 *  Attack, Defense, Health, and strength.
 */
character::character() : id(0), race(""), chanceAttack(0), chanceDefense(0), baseHealth(0), CharAttack(0), CharDefense(0), strength(0)
{
    //character chance of attack
	id=0;
	race="default";
	chanceAttack = chanceAttack + (rand() % 33);
    //character chance of defense
	chanceDefense = chanceDefense + (rand() % 50);
    //character health
	baseHealth = baseHealth + 60;
    //character attack
    CharAttack = CharAttack + 30;
    //character defense
    CharDefense = CharDefense + 20;
    //strength
    strength = strength + 100;
}
/*Attack(character& enemy)
 * This is the main combat function of the program
 * It determines wether or not an attack was successful, blocked or missed
 * It deducts the correct amount of health based on the hit to both the enemy and player
 * As the player are the only characters moving on the board
 * it is safe to assume the player made the attack
 * And the enemy character retaliated
 */
void character::Attack(character& enemy, bool night) {
	// Generate a numbers between 1 and 100
    // the generated numbers will be compared with
    // the chance of attack and defense to see if the
    // attack or defnese was succesful
	unsigned int playerCAttack  = (rand() % 100) + 1;
	unsigned int playerCDefense = (rand() % 100) + 1;
	//player
 
	unsigned int enemyCAttack  = (rand() % 100) + 1;
	unsigned int enemyCDefense = (rand() % 100) + 1;
	//enemy
	
	// attack will hit if the player chance attack is greater than the random attack chance
	if (playerCAttack < chanceAttack) {
        //defense will occur if the random enemy defence is greter than the enemy chanceDefence
        if(enemyCDefense > enemy.chanceDefense){
            //if not blocked full attack will hit
            for(unsigned int j = 0; j < (CharAttack); ++j){
                --enemy.baseHealth;
            }
          std::cout << "Enemy Failed to Block!" << std::endl;
        }
        else{
          //if blocked the attack - defence will hit
          int adjustedDamage = CharAttack - enemy.CharDefense;
          for(unsigned int j = 0; j < (adjustedDamage); ++j){
                  Ability(enemy, night, adjustedDamage); //--enemy.baseHealth
          }
          std::cout << "Enemy Blocked!" << std::endl;
        }
	}
    else {
        //otherwise the enemy will avoid the attack
		std::cout << "Enemy Avoided Attack" << std::endl;
	}
	// attack will hit if the enemy chance attack is greater than the random attack chance
	// and the random player defence chance is greter than the player chanceDefence
	if (enemyCAttack < enemy.chanceAttack) {
        //defense will occur the random player defence chance is greter than the player chanceDefence
        if(playerCDefense > chanceDefense){
            //if not blocked full attack will hit
            for(unsigned int j = 0; j < (enemy.CharAttack); ++j){
                --baseHealth;
		
            }
		std::cout << "Player Hit!" << std::endl;
        }
        else{
             //if blocked the attack - defence will hit
             int adjustedDamage2 = CharAttack - enemy.CharDefense;
             for(unsigned int j = 0; j < (adjustedDamage2); ++j){
			Ability(character(), night, adjustedDamage2);   //--baseHealth;
             }
          std::cout << "Player Blocked!" << std::endl;
        }
	} else {
        //otherwise the player will avoid the attack
		std::cout << "Player Missed!" << std::endl;
	}
    // Print out player health and enemy health
	std::cout << "Player Health:" << baseHealth << std::endl;
	std::cout << "Enemy Health:" << enemy.baseHealth << std::endl;
}

/*IsDead()
 *  Checks wether the character in question is dead
 */
bool character::IsDead() {
    return (baseHealth <= 0);
}

/*Ability(character)
 *  Used to give each individual race it's unique ability 
 */
void character::Ability(character,bool night, int aD ){

	if(race=="Human"){
		baseHealth = baseHealth;
	}
	if(race=="Elf"){
		baseHealth = baseHealth+1;
	}
	if(race=="Dwarf"){
		baseHealth=baseHealth;
	}
	if(race=="Hobbit"){
		baseHealth=baseHealth - (1+(rand()%5));
	}
	if(race=="Orc"){
        if(night == true){
          baseHealth = baseHealth+1;
        }
        else if (night == false){
          baseHealth=baseHealth-(int)(aD/4);
        }
		
	}
}






