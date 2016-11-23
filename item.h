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
        unsigned int weight;
        string name;
        
        int getWeight()
        {
            return weight;
        }


        string getname()
          {
             return name;
          }

        void setweight(int a)
        {
            weight =a;
        }

        void setname (string b)
        {
            name = b;
        }


};

//class weapon:public item
//{
//    public:
//        weapon();
//        int damage; 
//};
#endif
