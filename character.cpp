#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
#include "character.h"
using namespace std;

character::character() : chanceAttack(0), chanceDefense(0), baseHealth(0), CharAttack(0), CharDefense(0)
{
	chanceAttack = chanceAttack + (rand() % 33);
	chanceDefense = chanceDefense + (rand() % 50);
	baseHealth = baseHealth + 60;
    CharAttack = CharAttack + 30;
    CharDefense = CharDefense + 20;
	// these are used to generate the chance of attack currently all
	// attacks will do 1 damage
	// eAttack and pDefence/pAttack and eDefence will be the taken from each other
	// and the result will be the number of loops of --basehealth
}

void character::Attack(character& enemy) {
	// Generate a numbers between 1 and 100
	unsigned int playerCAttack  = (rand() % 100) + 1;
	unsigned int playerCDefense = (rand() % 100) + 1;
	//player 
	unsigned int enemyCAttack  = (rand() % 100) + 1;
	unsigned int enemyCDefense = (rand() % 100) + 1;
	//enemy
	
	// attack will hit if the player chance attack is greater than the random attack chance
	// and the random enemy defence is greter than the enemy chanceDefence 
	if (playerCAttack < chanceAttack) {
        if(enemyCDefense > enemy.chanceDefense){
            for(unsigned int j = 0; j < (CharAttack); ++j){
                --enemy.baseHealth;
            }
          std::cout << "Enemy Failed to Block!" << std::endl;
        }
        else{
          for(unsigned int j = 0; j < (CharAttack - enemy.CharDefense); ++j){
                  --enemy.baseHealth;
          }
          std::cout << "Enemy Blocked!" << std::endl;
        }
	}else {
		std::cout << "Enemy Avoided Attack" << std::endl;
	}
	// attack will hit if the enemy chance attack is greater than the random attack chance
	// and the random player defence chance is greter than the player chanceDefence
	if (enemyCAttack < enemy.chanceAttack) {
        if(playerCDefense > chanceDefense){
            for(unsigned int j = 0; j < (enemy.CharAttack); ++j){
                --baseHealth;
            }
		std::cout << "Player Hit!" << std::endl;
        }else{
             for(unsigned int j = 0; j < (enemy.CharAttack - CharDefense); ++j){
                 --baseHealth;
             }
          std::cout << "Player Blocked!" << std::endl;
        }
	} else {
		std::cout << "Player Missed!" << std::endl;
	}
	std::cout << "Player Health:" << baseHealth << std::endl;
	std::cout << "Enemy Health:" << enemy.baseHealth << std::endl;
}

bool character::IsDead() {
    return (baseHealth <= 0);
}

