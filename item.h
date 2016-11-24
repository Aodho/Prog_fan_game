// Header file for the Item class
//
// Contains very basic item structure.
// authors: Hugh, Conor, Diarmuid
// date:    12.11.2016
//////////////////////////////////////////////////////////////////////
#include <string>

#ifndef ITEM_H
#define ITEM_H

using namespace std;

class item
{
    public:
        item();

        item(int i)
        {
            id = i;
        }
        
        int getID()
        {
            return id;
        }

        int getWeight()
        {
            return weight;
        }

        int getHealth()
        {
            return health;
        }

        int getAttack()
        {
            return attack;
        }

        int getDefense()
        {
            return defense;
        }

        string getname()
        {
             return name;
        }

        string getType()
        {
            return type;
        }

        int getStrength()
        {
            return strength;
        }

        void setStrength(int s)
        {
            strength =s;
        }

        void setType(string t)
        {
            type =t;
        }

        void setweight(int w)
        {
            weight =w;
        }

        void setHealth(int h)
        {
            health = h;
        }

        void setAttack(int a)
        {
            attack = a;
        }

        void setDefense(int d)
        {
            defense = d;
        }

        void setname (string n)
        {
            name = n;
        }
        void setID(int i)
        {   
            id = i;
        }


        void setUpItem(int i)
        {
            if(i==1){
                setname("Sword");
                setAttack(10);
                setweight(10);
                setStrength(0);
                setType("Weapon");
                setID(1);
            }
            else if(i==2){
                setname("Dagger");
                setAttack(5);
                setweight(5);
                setStrength(0);
                setType("Weapon");
                setID(2);
            }
            else if(i==3){
                setname("Plate Armour");
                setAttack(-5);
                setDefense(10);
                setweight(40);
                setStrength(0);
                setType("Armour");
                setID(3);
            }
            else if(i==4){
                setname("Leather Armour");
                setDefense(5);
                setweight(20);
                setStrength(0);
                setType("Armour");
                setID(4);
            }
            else if(i==5){
                setname("Large Shield");
                setAttack(-5);
				setDefense(10);
                setweight(30);
                setStrength(0);
                setType("Shield");
                setID(5);
            }
            else if(i==6){
                setname("Small Shield");
                setDefense(5);
                setweight(10);
                setStrength(0);
                setType("Shield");
                setID(6);
            }
            else if(i==7){
                setname("Ring of Life");
                setHealth(10);
                setweight(1);
                setStrength(0);
                setType("Ring");
                setID(7);
            }
            else if(i==8){
                setname("Ring of Strength");
				setStrength(50);
                setHealth(-10);
                setweight(1);
                setType("Ring");
                setID(8);
            }
        }
    private:
        unsigned int id;
        string name;
        unsigned int weight;
		unsigned int strength;
        int health;
        int attack;
        string type;
        unsigned int defense;
};

#endif
