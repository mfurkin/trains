/*
 * KeyAlreadyExistsException.cpp
 *
 *  Created on: 8 ???. 2016 ?.
 *      Author: mfurkin
 */

#include "KeyAlreadyExistsException.h"

namespace std
{

KeyAlreadyExistsException::KeyAlreadyExistsException ():TrainObjectCreatingException()
{
}

KeyAlreadyExistsException::KeyAlreadyExistsException (const KeyAlreadyExistsException& aKeyAlreadyExistsException):TrainObjectCreatingException(aKeyAlreadyExistsException)
{
}

KeyAlreadyExistsException::KeyAlreadyExistsException (const string& aName):TrainObjectCreatingException(),name(aName)
{
}

int KeyAlreadyExistsException::getType()
{
    return KEY_ALREADY_EXISTS_TYPE;
}
KeyAlreadyExistsException::~KeyAlreadyExistsException ()
{
}

} /* namespace std */
