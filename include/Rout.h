/*
 * Rout.h
 *
 *  Created on: 22 ????. 2016 ?.
 *      Author: mfurkin
 */

#ifndef JSON_LIB_ROUT_H_
#define JSON_LIB_ROUT_H_
#define GLIBCXX_DEBUG


#include <time.h>
#include <vector>
#include "Station.h"
namespace std {

class Rout : public Saveable {
private:
	static string START_TIME_FIELD_NAME,ROUT_FIELD_NAME;
	vector<string> rout;
	time_t startTime;
public:
	Rout();
	Rout(const Rout& aRout);
	Rout(vector<string>& aRout, time_t aStartTime);
	int scheduleRout(map<string, Station> aStations, map<string, Line>& lines, TimeKeeper& timeKeeper);
	int operator == (Rout& aRout);
	Rout& operator =(const Rout& aRout);
	void saveMe(IntSaver anIntSaver, StringSaver aStringSaver, StringArraySaver aStrArrSaver);
//	void saveMe(rapidjson::Value& array, function<void(rapidjson::Value& array, vector<string>& aRout, time_t aTime)> aDataSaver);
	virtual ~Rout();
};

} /* namespace std */

#endif /* JSON_LIB_ROUT_H_ */
