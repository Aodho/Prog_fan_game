// Character class
//
// Contains character, attack function and special ability function.
// authors: Hugh, Conor, Diarmuid
// date:    12.11.2016
//////////////////////////////////////////////////////////////////////

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
	id=0;
	race="";
        //character chance of attack
	chanceAttack = 0;
    	//character chance of defense
	chanceDefense = 0;
    	//character health
	baseHealth = 0;
    	//character attack
    	CharAttack = 0;
    	//character defense
    	CharDefense = 0;
    	//strength
    	strength = 0;
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

	int adjustedDamage = CharAttack - enemy.CharDefense;//used to calculate player damage

	// attack will hit if the player chance attack is greater than the random attack chance
	if (playerCAttack < chanceAttack) {
        //defense will occur if the random enemy defence is greter than the enemy chanceDefence
		if(enemyCDefense > enemy.chanceDefense){
		    //if not blocked full attack - defense will hit
		    for(unsigned int j = 0; j < (adjustedDamage); ++j){
		        --enemy.baseHealth;//remove health for the adjusted Damage
		    }
		  std::cout << "Enemy Failed to Block!" << std::endl;
		}

        else{
	        //if a succesful defense races ability will take effect
	        Ability(enemy, night, adjustedDamage);
            std::cout << "Enemy Blocked Your Attack!" << std::endl;
        }
	}

	else {
		//otherwise the enemy will avoid the attack
		std::cout << "Enemy Avoided Your Attack" << std::endl;
	}

	int adjustedDamage2 = CharAttack - enemy.CharDefense;//used to calculate enemy damage

    //attack will hit if the enemy chance attack is greater than the random attack chance
	if (enemyCAttack < enemy.chanceAttack) {
	//defense will occur the random player defence chance is greter than the player chanceDefence

		if(playerCDefense > chanceDefense){
		    //if not blocked full attack - defense will hit
		    for(unsigned int j = 0; j < (adjustedDamage2); ++j){
		        --baseHealth;
			}

			std::cout << "Player Hit By Enemy!" << std::endl;
		}
		else{
		     //if a successful defense races ability will take effect
            Ability(character(), night, adjustedDamage2);
		  	std::cout << "Player Blocked Enemy Attack!" << std::endl;
		}
	} 
	else{
        //otherwise the player will avoid the attack
		std::cout << "Player Missed By Enemy!" << std::endl;
	}

    	// Print out player health and enemy health
	std::cout << "Player Health:" << baseHealth << std::endl;
	std::cout << "Enemy Health:" << enemy.baseHealth << std::endl;
}


/*IsDead()
 *  Checks whether the character in question is dead
 */

bool character::IsDead() {
    return (baseHealth <= 0);
}

/*Ability(character)
 *  Used to give each individual race it's unique ability 
 */
void character::Ability(character,bool night, int aD ){

	if(race=="Human"){
		baseHealth = baseHealth; //Human: Successful defences never cause damage.
	}
	if(race=="Elf"){
		baseHealth = baseHealth+1;//Elf: Successful defences always increases health by 1
	}
	if(race=="Dwarf"){
		baseHealth=baseHealth; //Dwarf: Successful defences never cause damage
	}
	if(race=="Hobbit"){
		baseHealth=baseHealth - (1+(rand()%5)); //Hobbit: Successful defences cause 0-5 damage regardless of attack value
	}
	if(race=="Orc"){
        if(night == true){
          baseHealth = baseHealth+1; //Orc: During night-time, successful defences cause increase of health by 1
        }
        else if (night == false){
          baseHealth=baseHealth-(int)(aD/4); //Orc: During day-time, successful defences cause 1/4 of adjusted damage.
        }
		
	}
}






