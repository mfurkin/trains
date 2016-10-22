/*
 * TimeKeeper.cpp
 *
 *  Created on: 20 ???. 2016 ?.
 *      Author: mfurkin
 */
#include <algorithm>
#include "Line.h"
#include "TimeKeeper.h"

namespace std
{

    TimeKeeper::TimeKeeper ()
    {
    }

    TimeKeeper::~TimeKeeper ()
    {
	clearAll();
    }

    void TimeKeeper::clearAll ()
    {
	times.clear();
    }
    void TimeKeeper::addTimeStations (string& firstStation, string& secondStation, time_t time)
    {
	string st = Line::getLineName(firstStation,secondStation);
	addTimeLine(st,time);
    }

    void TimeKeeper::addTimeLine (string& lineName, time_t time)
    {
	times.insert(TimeKeepingPair(lineName,time));
    }

    TimeKeepingRange TimeKeeper::getTimesStations (string& firstStation, string& secondStation)
    {
	string st = Line::getLineName(firstStation,secondStation);
	return getTimeLine(st);
    }

    TimeKeepingRange TimeKeeper::getTimeLine (string& lineName)
    {
	return times.equal_range(lineName);
    }


    int TimeKeeper::countFilter (TimeKeepingFilter filter)
    {
	return count_if(times.begin(),times.end(),filter);
    }

    bool TimeKeeper::checkAll (TimeKeepingFilter filter)
    {
	return all_of(times.begin(),times.end(),filter);
    }

    bool TimeKeeper::checkNone (TimeKeepingFilter filter)
    {
	return none_of(times.begin(),times.end(),filter);

    }

} /* namespace std */


