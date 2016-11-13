//Class for custom game exceptions
//
//
// authors: Hugh, Conor, Diarmuid
// date:  12.11.2016
//////////////////////////////////////////////////////////////////////
#include "boardException.h"

boardException::boardException()
{
        exceptionName = "Exception: Board size incorrectly defined!";
            sizeErr = "Size is should be a postive interger";
}


boardException::boardException(string name)
{
        exceptionName = name;
}

string boardException::getException()
{
        return exceptionName;
}

