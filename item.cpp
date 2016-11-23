#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
#include "item.h"
using namespace std;
item::item() : id(0), weight(0), name(""), attack(0), defense(0), health(0)
{
    id = 0;
	weight = 0;
	name = "Defluat";
    attack = 0;
    defense = 0;
    health = 0;
}

/*item::item(int id)
{
    id;
}*/


//item weapon::weapon(): weight(0), name(""), damage(0)
//{
//	name = "";
//	weight = 0;
//	damage = 0;
//}
