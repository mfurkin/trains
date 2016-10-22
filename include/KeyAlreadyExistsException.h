/*
 * KeyAlreadyExistsException.h
 *
 *  Created on: 8 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef KEYALREADYEXISTSEXCEPTION_H_
#define KEYALREADYEXISTSEXCEPTION_H_
#include <string>
#include "TrainObjectCreatingException.h"
namespace std
{

    class KeyAlreadyExistsException: public TrainObjectCreatingException
    {
    private:

	string name;
    public:
	static const int KEY_ALREADY_EXISTS_TYPE = 2;
	KeyAlreadyExistsException();
	KeyAlreadyExistsException(const KeyAlreadyExistsException& aKeyAlreadyExistsException);
	KeyAlreadyExistsException (const string& aName);
	int getType();
	virtual	~KeyAlreadyExistsException ();
    };

} /* namespace std */

#endif /* KEYALREADYEXISTSEXCEPTION_H_ */
