/*
 * Station.cpp
 *
 *  Created on: 22 ????. 2016 ?.
 *      Author: mfurkin
 */

#include <algorithm>
#include "DataKeeper.h"
#include "Line.h"
#include "Station.h"
#include <iostream>

namespace std {

DataKeeper& Station::keeper = DataKeeper::getKeeper();
string Station::NAME_FIELD_NAME = string("name");
string Station::WAYS_QTY_FIELD_NAME = string("waysQty");
Station::Station ():name("noname")
{
}

Station::Station (const Station& aStation):name(aStation.name)
{
    keeper.copy(name);
}

Station::Station (string aName, int aWaysQty):name(aName)
{
    keeper.add(name,aWaysQty);
}

Station::~Station()
{
    keeper.remove(name);
}
Station& Station::operator = (const Station& aStation)
{
    if (&aStation != this)
    {
	string oldname = name;
	name = aStation.name;
	keeper.copy(name);
	keeper.remove(oldname);
    }
    return *this;
}
int Station::operator == (const Station& aStation)
{
    return name == aStation.name;
}

int Station::getWaysQty () const
{
    return keeper.getData(name);
}

int Station::checkOnStation (time_t aTime,TimeKeeper& timeKeeper)
{
    return keeper.checkOnStation(aTime, timeKeeper, name);
}

int Station::checkOnLine (time_t time, string& stationName, TimeKeeper& timeKeeper)
{
    return keeper.checkOnLine(time,stationName,timeKeeper,name);
}

time_t Station::addTime (time_t time, string& nextStation, TimeKeeper& timeKeeper)
{
    return keeper.addTime(time,nextStation, timeKeeper,name);
}

void Station::addMe (map<string, Station>& aMap)
{
    aMap[name] = *this;
}
/*
void Station::saveMe(rapidjson::Value& array, function<void(rapidjson::Value&, string&, int)> aDataSaver)
{
    aDataSaver(array,name,getWaysQty());
}
*/
void Station::saveMe (IntSaver anIntSaver, StringSaver aStringSaver, StringArraySaver aStrArrSaver)
{
    aStringSaver(NAME_FIELD_NAME,name);
    anIntSaver(WAYS_QTY_FIELD_NAME,getWaysQty());
}
} /* namespace std */


