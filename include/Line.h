/*
 * Line.h
 *
 *  Created on: 7 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef LINE_H_
#define LINE_H_
#include <functional>
#include <string>
#include "rapidjson/document.h"
#include"DataKeeper.h"
#include "Saveable.h"

namespace std
{
class Line : public Saveable
{
private:
    static DataKeeper& keeper;
    static string FIRST_STATION_FIELD_NAME,SECOND_STATION_FIELD_NAME,LENGTH_FIELD_NAME;
    string firstStation, secondStation,name;
    int getLength();
    void checkStation(string& name);
public:
    Line();
    Line(const Line& aLine);
    Line (const string& aFirstStation, const string& aSecondStation, int aLength);
    static string getLineName(string& aFirst, string& aSecond);
    Line& operator =(const Line& aLine);
//  time_t scheduleSecondStation(time_t aFirstStationTime);
    int checkTimes(time_t time1, time_t time2);
    void addMe(map<string, Line>& lines);
    void saveMe(IntSaver anIntSaver, StringSaver aStringSaver, StringArraySaver aStrArrSaver);
//  void saveMe(rapidjson::Value& array, function<void(rapidjson::Value& array, string&, string&, int)> aDataSaver);
    virtual ~Line ();
};
}
#endif /* LINE_H_ */
