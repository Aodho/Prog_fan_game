// Item class
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
#include "item.h"
using namespace std;

/*item()
 *  setting up the default Item object.
 *  setting default values for ID, Weight, name, 
 *  Attack, Defense, Health.
 */

item::item() : id(0), weight(0), name(""), attack(0), defense(0), health(0)
{
    id = 0;
	weight = 0;
	name = "";
    attack = 0;
    defense = 0;
    health = 0;
}


