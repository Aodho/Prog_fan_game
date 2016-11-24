#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
#include "character.h"
#include "fanGame.h"
using namespace std;

//character class used to generate characters
character::character() : chanceAttack(0), chanceDefense(0), baseHealth(0), CharAttack(0), CharDefense(0), strength(0)
{
    //character chance of attack
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

//Used for when the player attacks an enemy
void character::Attack(character& enemy) {
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
          for(unsigned int j = 0; j < (CharAttack - enemy.CharDefense); ++j){
                  --enemy.baseHealth;
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
             for(unsigned int j = 0; j < (enemy.CharAttack - CharDefense); ++j){
                 --baseHealth;
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

//check if the character in question is dead
bool character::IsDead() {
    return (baseHealth <= 0);
}

