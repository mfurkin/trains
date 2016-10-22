/*
 * Scheduler.cpp
 *
 *  Created on: 11 ???. 2016 ?.
 *      Author: mfurkin
 */
#include <algorithm>
#include <map>

#include "Scheduler.h"

namespace std
{
    Scheduler::Scheduler ():routs()
    {
    }

    Scheduler::Scheduler (const Scheduler& aScheduler):stations(aScheduler.stations), lines(aScheduler.lines), routs(aScheduler.routs)
    {
    }

    Scheduler::Scheduler (vector<Station> aStations, vector<Line> aLines, vector<Rout> aRouts):stations(aStations),lines(aLines),routs(aRouts)
    {
    }
    int Scheduler::schedule ()
    {
	int result = 0;

	map<string,Station> stations = createStations();

	map<string, Line> lines2 = createLines();

	TimeKeeper timeKeeper;
	result = all_of(routs.begin(),routs.end(),[&stations,&lines2,&timeKeeper](Rout& aRout)->bool
	{
	    return  aRout.scheduleRout(stations, lines2, timeKeeper);
	});

	return result;
    }

    map<string, Station> Scheduler::createStations()
    {

	map<string, Station> result;
	for_each(stations.begin(),stations.end(),[&result](Station& curStation)
	{
	    curStation.addMe(result);
	});

	return result;
    }

    map<string, Line>  Scheduler::createLines ()
    {
	map<string, Line> result;
	for_each(lines.begin(),lines.end(),[&result](Line& curLine)
	{
	    curLine.addMe(result);
	});
	return result;
    }

    void
    std::Scheduler::clearAllSchedules ()
    {
    }

    Scheduler::~Scheduler ()
    {
    }

} /* namespace std */


