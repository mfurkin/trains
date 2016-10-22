/*
 * StationSaver.cpp
 *
 *  Created on: 8 ???. 2016 ?.
 *      Author: mfurkin
 */

#include <DataKeeper.h>
#include <algorithm>
#include <functional>
#include "KeyAlreadyExistsException.h"

namespace std
{
    DataKeeper::DataKeeper ():dataKeep(),instanceQtyKeep()
    {
    }

    DataKeeper&  DataKeeper::getKeeper ()
    {
	static DataKeeper keeper;
	return keeper;
    }

    int DataKeeper::exists (string& name)
    {
	map<string, int>::iterator it = instanceQtyKeep.find(name);
	return (it != instanceQtyKeep.end()) && it->second;
    }

    void DataKeeper::add (string& name, int data)
    {
	if (exists(name))
	    throw KeyAlreadyExistsException(name);
	dataKeep[name] = data;
	instanceQtyKeep[name] = 1;
    }

    void DataKeeper::copy (string& name)
    {
	int copies = instanceQtyKeep[name];
	instanceQtyKeep[name] = ++copies;
    }

    void DataKeeper::remove (string& name)
    {
	if (exists(name))
	{
	    int copies = instanceQtyKeep[name];
	    if (copies-- == 1)
		instanceQtyKeep.erase(name);
	    else
		instanceQtyKeep[name] = copies;
	}
    }

    int DataKeeper::getData (const string& name)
    {
	return dataKeep[name];
    }


    DataKeeper::~DataKeeper ()
    {
    }

} /* namespace std */
