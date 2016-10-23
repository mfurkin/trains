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


namespace std {

DataKeeper& Station::keeper = DataKeeper::getKeeper();

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
//  return name == aStation.name && getWaysQty() == aStation.getWaysQty();
    return name == aStation.name;
}

int Station::getWaysQty () const
{
    return keeper.getData(name);
}
/*
time_t Station::scheduleSecondStation(Line aLine, time_t aTime)
{
//  return aLine.scheduleSecondStation(aTime);
    return keeper.scheduleSecondStation(aTime,name);
}
*/
int Station::checkOnStation (time_t aTime,TimeKeeper& timeKeeper)
{
    return keeper.checkOnStation(aTime, timeKeeper, name);
}

int Station::checkOnLine (time_t time, string& stationName, TimeKeeper& timeKeeper)
{
    return keeper.checkOnLine(time,stationName,timeKeeper,name);
}

time_t Station::addTime (time_t time, string& nextStation, TimeKeeper& timeKeeper)
{/*
    string lineName = Line::getLineName(name,nextStation);
    string msg("after insert");

    time_t endTime = lines[Line::getLineName(name,nextStation)].scheduleSecondStation(time);
    timeKeeper.addTimeStations(name,nextStation,time);
    return endTime;
    */
    return keeper.addTime(time,nextStation, timeKeeper,name);
}

void Station::addMe (map<string, Station>& aMap)
{
    aMap[name] = *this;
}

void Station::saveMe(rapidjson::Value& array, function<void(rapidjson::Value&, string&, int)> aDataSaver)
{
    aDataSaver(array,name,getWaysQty());
}


} /* namespace std */


