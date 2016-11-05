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
#include "Saveable.h"
namespace std {

class Station : public Saveable
{
private:
	string name;
	static DataKeeper& keeper;
	int getWaysQty () const;
public:
	static string NAME_FIELD_NAME, WAYS_QTY_FIELD_NAME;
	Station();
	Station(const Station& aStation);
	Station(string& aStation);
	Station(string aName, int aWaysQty);
	virtual ~Station();
	int operator == (const Station& aStation);
	Station& operator = (const Station& sStation);
	int checkOnLine(time_t time,string& secondStationName, TimeKeeper& timeKeeper);
	int checkOnStation(time_t aTime, TimeKeeper& timeKeeper);
	time_t addTime(time_t time, string& nextStation, TimeKeeper& timeKeeper);
	void addMe(map<string,Station>& aMap);
	void saveMe(IntSaver anIntSaver, StringSaver aStringSaver, StringArraySaver aStrArrSaver);
//	void saveMe(rapidjson::Value& array, function<void(rapidjson::Value&, string&, int)> aDataSaver);
    };

} /* namespace std */

#endif /* JSON_LIB_STATION_H_ */
