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
    return name == aStation.name && getWaysQty() == aStation.getWaysQty();
}

int Station::getWaysQty () const
{
    return keeper.getData(name);
}

time_t Station::scheduleSecondStation(Line aLine, time_t aTime)
{
    return aLine.scheduleSecondStation(aTime);
}

int Station::checkOnStation (time_t aTime,TimeKeeper& timeKeeper)
{
    rapidjson::Value value(rapidjson::kObjectType);
    int num = 0;

    num = timeKeeper.countFilter([aTime](TimeKeepingPair curPair)
    {
	return (curPair.second == aTime);
    });
    int waysQty = getWaysQty();
    return (num<waysQty);
}
/*
Line  Station::getLine(string& secondStationName, map<string,Line> lines)
{
    return lines[Line::getLineName(name,secondStationName)];
}
*/
int Station::checkOnLine (time_t time, string& stationName, map<string, Line>& lines, TimeKeeper& timeKeeper)
{
    int result = 0;
    string lineName = Line::getLineName(stationName,name);
    result = timeKeeper.checkNone([time,&lineName](TimeKeepingPair curPair)->bool
	{
	    return (curPair.first == lineName) && (curPair.second == time);
	});
    if (result)
    {
	string lineName = Line::getLineName(name,stationName);
	TimeKeepingRange thisLineSchedule = timeKeeper.getTimesStations(name,stationName);
	Line thisLine = lines[lineName];
	result =  all_of(thisLineSchedule.first,thisLineSchedule.second,[time,&thisLine,&lineName](pair<string,time_t> curPair)mutable->bool
	    {
		return thisLine.checkTimes(curPair.second,time);
	    });
    }
    return result;
}

time_t Station::addTime (time_t time, string& nextStation, map<string, Line>& lines, TimeKeeper& timeKeeper)
{
    string lineName = Line::getLineName(name,nextStation);
    string msg("after insert");

    time_t endTime = lines[Line::getLineName(name,nextStation)].scheduleSecondStation(time);
//  time_t endTime = getLine(nextStation,lines).scheduleSecondStation(time);
    timeKeeper.addTimeStations(name,nextStation,time);
    return endTime;
}

void Station::addMe (map<string, Station>& aMap)
{
    aMap[name] = *this;
}

void Station::saveMe(rapidjson::Value& array, function<void(rapidjson::Value&, string&, int)> aDataSaver)
{
    aDataSaver(array,name,getWaysQty());
}

int Station::checkStation (int num)
{
    int waysQty = getWaysQty();
    return (num<waysQty);
}



} /* namespace std */


