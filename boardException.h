// FantasyGame custom exception class
//
//
// authors: Hugh, Conor, Diarmuid
// date:  12.11.2016
//////////////////////////////////////////////////////////////////////

#ifndef BOARDEXCEPTION_H
#define BOARDEXCEPTION_H

#include <string>
#include <exception>

using std::string;

class boardException
{

    public:
        boardException();
        //generic constructor with message set
        boardException(string str);
        //get the message
        string getException();

    private:
        string exceptionName;
        string sizeErr;
};

#endif
