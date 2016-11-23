#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <vector>
#include "item.h"
using namespace std;
item::item() : weight(0), name("")
{
    //weight of item
	weight = 5;
	name = "blah";
}

//item weapon::weapon(): weight(0), name(""), damage(0)
//{
//	name = "";
//	weight = 0;
//	damage = 0;
//}
