/*
 * StationSaver.cpp
 *
 *  Created on: 8 ???. 2016 ?.
 *      Author: mfurkin
 */

#include <DataKeeper.h>
#include <algorithm>
#include <functional>
#include "rapidjson/Document.h"
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

    int DataKeeper::checkOnLine (time_t time, string& stationName, TimeKeeper& timeKeeper, string& name)
    {
	 int result = 0;
	    string lineName = DataKeeper::getLineName(stationName,name);
	    result = timeKeeper.checkNone([time,&lineName](TimeKeepingPair curPair)->bool
		{
		    return (curPair.first == lineName) && (curPair.second == time);
		});
	    if (result)
	    {
		TimeKeepingRange thisLineSchedule = timeKeeper.getTimesStations(name,stationName);
		int length = dataKeep[DataKeeper::getLineName(name,stationName)];
		result =  all_of(thisLineSchedule.first,thisLineSchedule.second,[time,length](pair<string,time_t> curPair)mutable->bool
		    {
			return abs(curPair.second-time) >= length;
		    });
	    }
	    return result;
    }

    int DataKeeper::checkOnStation (time_t aTime, TimeKeeper& timeKeeper, string& name)
    {
	rapidjson::Value value(rapidjson::kObjectType);
	int num = 0;

	num = timeKeeper.countFilter([aTime](TimeKeepingPair curPair)
	{
	    return (curPair.second == aTime);
	});
	int waysQty = dataKeep[name];
	return (num<waysQty);
    }

    int DataKeeper::getData (const string& name)
    {
	return dataKeep[name];
    }


    DataKeeper::~DataKeeper ()
    {
    }

    string  DataKeeper::getLineName (string& aFirst, string& aSecond)
    {
	char* buf = new char [aFirst.length()+aSecond.length()+3];
	strcpy(buf,aFirst.c_str());
	strcat(buf,"->");
	strcat(buf,aSecond.c_str());
	return string(buf);
    }
    time_t DataKeeper::addTime (time_t time, string& nextStation, TimeKeeper& timeKeeper, string& name)
    {
	string lineName = DataKeeper::getLineName(name,nextStation);
        time_t endTime = time+dataKeep[lineName];
        timeKeeper.addTimeLine(lineName,time);
        return endTime;
    }

} /* namespace std */


