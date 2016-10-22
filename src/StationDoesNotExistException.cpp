/*
 * StationDoesNotExist.cpp
 *
 *  Created on: 8 ???. 2016 ?.
 *      Author: mfurkin
 */

#include "StationDoesNotExistException.h"

namespace std
{
    StationDoesNotExistException::StationDoesNotExistException ():TrainObjectCreatingException()
    {
    }

    StationDoesNotExistException::StationDoesNotExistException (const StationDoesNotExistException& aStationDoesNotExistException):TrainObjectCreatingException(aStationDoesNotExistException), name(aStationDoesNotExistException.name)
    {
    }
    StationDoesNotExistException::StationDoesNotExistException (string aName):TrainObjectCreatingException(),name(aName)
    {
    }

    int StationDoesNotExistException::getType()
    {
	return STATION_DOES_NOT_EXISTS_TYPE;
    }

    StationDoesNotExistException::~StationDoesNotExistException ()
    {
    }

} /* namespace std */
