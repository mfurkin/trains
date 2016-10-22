/*
 * TrainObjectCreatingException.h
 *
 *  Created on: 10 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef TRAINOBJECTCREATINGEXCEPTION_H_
#define TRAINOBJECTCREATINGEXCEPTION_H_

namespace std
{

    class TrainObjectCreatingException
    {
    public:
	TrainObjectCreatingException ();
	virtual int getType() = 0;
	virtual	~TrainObjectCreatingException ();

    };

} /* namespace std */

#endif /* TRAINOBJECTCREATINGEXCEPTION_H_ */
