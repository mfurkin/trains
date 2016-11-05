/*
 * Line.cpp
 *
 *  Created on: 7 ???. 2016 ?.
 *      Author: mfurkin
 */

#include "Line.h"
#include "StationDoesNotExistException.h"

namespace std
{
DataKeeper& Line::keeper = DataKeeper::getKeeper();
string Line::FIRST_STATION_FIELD_NAME = string("firstStation");
string Line::SECOND_STATION_FIELD_NAME = string("secondStation");
string Line::LENGTH_FIELD_NAME = string("length");
Line::Line ()
{
}

Line::Line (const Line& aLine):firstStation(aLine.firstStation),secondStation(aLine.secondStation),name(aLine.name)
{
    keeper.copy(name);
}

Line::Line (const string& aFirstStation, const string& aSecondStation, int aLength):firstStation(aFirstStation), secondStation(aSecondStation)
{

    checkStation(firstStation);

    checkStation(secondStation);

    name = getLineName(firstStation,secondStation);

    string st2(getLineName(secondStation,firstStation));

    keeper.add(name,aLength);

    keeper.add(st2,aLength);

}

string Line::getLineName (string& aFirst, string& aSecond)
{
     char* buf = new char [aFirst.length()+aSecond.length()+3];
     strcpy(buf,aFirst.c_str());
     strcat(buf,"->");
     strcat(buf,aSecond.c_str());
     return string(buf);;
}
void Line::saveMe(IntSaver anIntSaver, StringSaver aStringSaver, StringArraySaver aStrArrSaver)
{
    aStringSaver(FIRST_STATION_FIELD_NAME,firstStation);
    aStringSaver(SECOND_STATION_FIELD_NAME,secondStation);
    anIntSaver(LENGTH_FIELD_NAME,getLength());
}
/*
void Line::saveMe (rapidjson::Value& array, function<void(rapidjson::Value& array, string&, string&, int)> aDataSaver)
{
    int length = getLength();
    aDataSaver(array,firstStation,secondStation,length);
}
*/
void Line::checkStation (string& station)
{
    if (!(keeper.exists(station)))
    	throw StationDoesNotExistException(station);
}

int Line::getLength ()
{
    return keeper.getData(name);
}

void Line::addMe (map<string, Line>& lines)
{
    string st2 = getLineName(secondStation,firstStation);
    lines[name] = *this;
    lines[st2] = *this;
}

Line& Line::operator = (const Line& aLine)
{
    if (&aLine != this)
    {
	(*this).firstStation = aLine.firstStation;
	(*this).secondStation = aLine.secondStation;
	(*this).name = aLine.name;
	keeper.copy(name);
    }
    return *this;
}

Line::~Line ()
{
    keeper.remove(name);
    string st = Line::getLineName(secondStation,firstStation);
    keeper.remove(st);
}

}


