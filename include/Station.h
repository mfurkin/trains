/*
 * Station.h
 *
 *  Created on: 22 ????. 2016 ?.
 *      Author: mfurkin
 */

#ifndef JSON_LIB_STATION_H_
#define JSON_LIB_STATION_H_

#include <DataKeeper.h>
#include <functional>
#include <map>
#include <string>
#include "rapidjson/allocators.h"
#include "rapidjson/document.h"
#include "TimeKeeper.h"
#include "Line.h"
namespace std {

class Station {
private:
	string name;
	static DataKeeper& keeper;
	int getWaysQty () const;
//	Line  getLine(string& secondStationName, map<string,Line> lines);
public:
	static const string STATION_NAME;
	Station();
	Station(const Station& aStation);
	Station(string& aStation);
	Station(string aName, int aWaysQty);
	virtual ~Station();
	time_t scheduleSecondStation(Line aLine, time_t aTime);
	int operator == (const Station& aStation);
	Station& operator = (const Station& sStation);
	int checkOnLine(time_t time,string& secondStationName, map<string, Line>& lines, TimeKeeper& timeKeeper);
	int checkOnStation(time_t aTime, TimeKeeper& timeKeeper);
	time_t addTime(time_t time, string& nextStation, map<string, Line>& lines, TimeKeeper& timeKeeper);
	void addMe(map<string,Station>& aMap);
	void saveMe(rapidjson::Value& array, function<void(rapidjson::Value&, string&, int)> aDataSaver);
	int checkStation(int num);
    };

} /* namespace std */

#endif /* JSON_LIB_STATION_H_ */