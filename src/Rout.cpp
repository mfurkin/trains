/*
 * Rout.cpp
 *
 *  Created on: 22 ????. 2016 ?.
 *      Author: mfurkin
 */

#include "Rout.h"

namespace std {



    Rout::Rout ():rout(),startTime(0)
    {
    }

    Rout::Rout (const Rout& aRout):rout(aRout.rout),startTime(aRout.startTime)
    {

    }

    Rout::Rout(vector<string>& aRout, time_t aStartTime):rout(aRout),startTime(aStartTime)
    {
    }

    int Rout::operator == (Rout& aRout)
    {
	int size = rout.size(),i,size2 = aRout.rout.size();

	int result = (startTime == aRout.startTime) && (size == size2);
	if (result)
	    for (i=0;(i<size) && (result=(rout[i] == aRout.rout[i]));i++)
	    {
	    }
	return result;
    }

    int Rout::scheduleRout(map<string, Station> aStations, map<string, Line>& lines, TimeKeeper& timeKeeper)
    {
	Station firstStation;
	string firstStationName, secondStationName,terminal("<terminal>");
	function<bool(Station& station, time_t time)> test,test1,test2;
	int i,size1 = rout.size() - 1;
	bool result = true;
	time_t curTime;
	curTime = startTime;
	test1 = [&test,&test2](Station& station, time_t time) -> bool
		{
		    test = test2;
		    return true;
		};
	test2 = [&curTime,&timeKeeper](Station& station, time_t time) -> bool
		{
		    return station.checkOnStation(time,timeKeeper);
		};
	test = test1;
	for(i=0;(i<size1) && (result);)
	{
	    firstStationName = rout[i++];
	    secondStationName = rout[i];
	    firstStation = aStations[firstStationName];
	    result = test(firstStation,curTime);
	    if (result)
	    {
		bool res2;
		Station secondStation = aStations[secondStationName];
		res2 = secondStation.checkOnLine(curTime,firstStationName,lines,timeKeeper);
		if (res2)
		    curTime = firstStation.addTime(curTime,secondStationName,lines,timeKeeper);
		result = res2;
	    }
	}
	return result;
    }

    Rout& Rout::operator = (const Rout& aRout)
    {
	if (this != &aRout)
	{
	    startTime = aRout.startTime;
	    rout = aRout.rout;
	}
	return *this;
    }

    Rout::~Rout()
    {
    }


    void Rout::saveMe (rapidjson::Value& array, function<void(rapidjson::Value& array, vector<string>& aRout, time_t aTime)> aDataSaver)
    {
	aDataSaver(array,rout, startTime);
    }

} /* namespace std */
