/*
 * Scheduler.h
 *
 *  Created on: 11 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include <map>
#include <vector>
#include "Line.h"
#include "Rout.h"
#include "Station.h"
namespace std
{
    class Scheduler
    {
    private:
	vector<Station> stations;
	vector<Line> lines;
	vector<Rout> routs;
	map<string, Station> createStations();
	map<string, Line> createLines();
    public:
	Scheduler();
	Scheduler(const Scheduler& aScheduler);
	Scheduler(vector<Station> aStations, vector<Line> aLines, vector<Rout> aRouts);
	virtual	~Scheduler ();
	void clearAllSchedules();
	int schedule();
    };

} /* namespace std */

#endif /* SCHEDULER_H_ */
