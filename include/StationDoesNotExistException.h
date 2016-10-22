/*
 * StationDoesNotExist.h
 *
 *  Created on: 8 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef STATIONDOESNOTEXISTEXCEPTION_H_
#define STATIONDOESNOTEXISTEXCEPTION_H_
#include <string>
#include "TrainObjectCreatingException.h"
namespace std
{

    class StationDoesNotExistException : public TrainObjectCreatingException
    {
    private:
	string name;
    public:
	static const int STATION_DOES_NOT_EXISTS_TYPE = 1;
	StationDoesNotExistException();
	StationDoesNotExistException(const StationDoesNotExistException& aStationDoesNotExistException);
	StationDoesNotExistException (string aName);
	int getType();
	virtual	~StationDoesNotExistException ();
    };

} /* namespace std */

#endif /* STATIONDOESNOTEXISTEXCEPTION_H_ */
