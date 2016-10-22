/*
 * JsonExchangerTest.cpp
 *
 *  Created on: 7 ???. 2016 ?.
 *      Author: mfurkin
 */



#include <fstream>
#include "JsonExchangerTest.h"
#include "KeyAlreadyExistsException.h"
#include "Station.h"
namespace std
{
    string JsonExchangerTest::STATIONS_FNAME = "D:\\tmp3\\stations.txt";
    string JsonExchangerTest::STATION_A_NAME = "StationA";
    string JsonExchangerTest::STATION_B_NAME = "StationB";
    string JsonExchangerTest::STATION_C_NAME = "StationC";
    string JsonExchangerTest::LINES_FNAME = "D:\\tmp3\\lines.txt";
    string JsonExchangerTest::ROUTS_FNAME = "D:\\tmp3\\routs.txt";
JsonExchangerTest::JsonExchangerTest ()
{
    stations[0] = Station (STATION_A_NAME, 2);
    stations[1] = Station (STATION_B_NAME, 3);
    stations[2] = Station (STATION_C_NAME, 4);
    lines[0] = Line (STATION_A_NAME, STATION_B_NAME, 10);
    lines[1] = Line (STATION_B_NAME, STATION_C_NAME, 20);
    lines[2] = Line (STATION_A_NAME, STATION_C_NAME, 30);
    stationsV = vector<Station>(3);
    linesV = vector<Line>(3);
    routs = vector<Rout>(4);
}

void JsonExchangerTest::readStationsTest ()
{
    int count = 0;

    stationsV = json.readStations(STATIONS_FNAME,[&count](TrainObjectCreatingException& toce)
    {
	count++;
    });

    assert(count == 3);

}

void JsonExchangerTest::createStations()
{
    if (!(stationsV.empty()))
	stationsV.clear();
    stationsV = vector<Station>(3);
    stationsV[0] = stations[0];
    stationsV[1] = stations[1];
    stationsV[2] = stations[2];
}
void JsonExchangerTest::writeStationsTest ()
{
    if (json.fileExists(STATIONS_FNAME))
	deleteStationsFile();
    createStations();
    json.writeStations (STATIONS_FNAME, stationsV);
}

void JsonExchangerTest::deleteStationsFile ()
{
    remove(STATIONS_FNAME.c_str());
}

void JsonExchangerTest::writeNetTest ()
{
    writeStationsTest();
    createNet();
    json.writeNet(LINES_FNAME,linesV);
}


void JsonExchangerTest::readNetTest ()
{
    int count = 0;
    linesV = json.readNet(LINES_FNAME,[&count](TrainObjectCreatingException& toce)
    {
	int type = toce.getType();
	if (type == KeyAlreadyExistsException::KEY_ALREADY_EXISTS_TYPE)
	    count++;
	else
	    assert(false);
    });

}

void JsonExchangerTest::createNet ()
{
    linesV[0] = lines[0];
    linesV[1] = lines[1];
    linesV[2] = lines[2];
}

void JsonExchangerTest::writeRoutsListTest ()
{
    createRoutsList();
    json.writeRoutsList(ROUTS_FNAME,routs);
}

void JsonExchangerTest::createRoutsList ()
{
    vector<string> rout1, rout2, rout3, rout4;
    rout1 = {"StationA","StationB","StationC"};
    rout2 = {"StationA","StationC","StationB"};
    rout3 = {"StationA","StaionB","StationC","StationA"};
    rout4 = {"StationA","StationC","StationB","StationA"};

    routs[0] = Rout(rout1,100);
    routs[1] = Rout(rout2,150);
    routs[2] = Rout(rout3,190);
    routs[3] = Rout(rout4,250);
}

void JsonExchangerTest::readRoutsListTest ()
{
    vector<Rout> routs2 = json.readRoutsList(ROUTS_FNAME,[](TrainObjectCreatingException& ex) {
	assert("false");
    });
    unsigned int size = routs.size(), size2 = routs2.size(),i= 0;
    assert(size2 == size);
    for (i=0;i<size;)
    {
	assert(routs[i] == routs2[i]);
    }
}

JsonExchangerTest::~JsonExchangerTest ()
{
}

}
