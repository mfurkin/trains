/*
 * TimeKeeper.h
 *
 *  Created on: 20 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_
#include <map>
#include <string>
#include <time.h>

namespace std
{
    typedef multimap<string,time_t> TimeKeepingMap;
    typedef multimap<string,time_t>::iterator TimeKeepingIterator;
    typedef pair<string, time_t> TimeKeepingPair;
    typedef pair<TimeKeepingIterator, TimeKeepingIterator> TimeKeepingRange;
    typedef function<bool(TimeKeepingPair curPair)> TimeKeepingFilter;
    class TimeKeeper
    {
    private:
	TimeKeepingMap times;
    public:
	TimeKeeper ();
	virtual	~TimeKeeper ();
	void addTimeStations(string& firstStation, string& secondStation, time_t time);
	void addTimeLine(string& LineName, time_t time);
	int countFilter(TimeKeepingFilter filter);
	bool checkAll(TimeKeepingFilter filter);
	bool checkNone(TimeKeepingFilter filter);
	void clearAll();
	TimeKeepingRange getTimesStations(string& firstStation, string& secondStation);
	TimeKeepingRange getTimeLine(string& lineName);
    };

} /* namespace std */

#endif /* TIMEKEEPER_H_ */
