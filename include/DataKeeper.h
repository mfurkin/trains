/*
 * StationSaver.h
 *
 *  Created on: 8 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef STATIONKEEPER_H_
#define STATIONKEEPER_H_
#include <map>
#include "TimeKeeper.h"
namespace std
{

    class DataKeeper
    {
    private:
	static DataKeeper& keeper;
	map<string, int> dataKeep;
	map<string, int> instanceQtyKeep;
	DataKeeper();
	~DataKeeper ();
    public:
	DataKeeper(const DataKeeper& aKeeper) = delete;
	DataKeeper& operator=(const DataKeeper&) = delete;
	static DataKeeper& getKeeper();
	static string getLineName(string& aFirst, string& aSecond);
	int exists(string& name);
	void add(string& name, int waysQty);
	void copy(string& name);
	void remove(string& name);
	time_t addTime(time_t time, string& nextStation, TimeKeeper& timeKeeper,string& name);
	int checkOnLine(time_t time, string& secondStationName, TimeKeeper& timeKeeper,string& name);
	int checkOnStation(time_t aTime, TimeKeeper& timeKeeper, string& name);
	int getData(const string& name);
    };

} /* namespace std */

#endif /* STATIONKEEPER_H_ */
