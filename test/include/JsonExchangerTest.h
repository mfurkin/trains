/*
 * JsonExchangerTest.h
 *
 *  Created on: 7 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef JSONEXCHANGERTEST_H_
#define JSONEXCHANGERTEST_H_
#include <vector>
#include "JsonExchanger.h"
#include "Station.h"

namespace std
{
class JsonExchangerTest
{
private:
    Station stations[3];
    Line lines[3];
    vector<Station> stationsV;
    vector<Line> linesV;
    vector<Rout> routs;
    JsonExchanger json;
    static string STATIONS_FNAME;
    static string STATION_A_NAME;
    static string STATION_B_NAME;
    static string LINES_FNAME;
    static string STATION_C_NAME;
    static string ROUTS_FNAME;
    void deleteStationsFile(string& fname);
    void createStations();
    void createNet();
    void createRoutsList();
public:
    JsonExchangerTest ();
    void readStationsTest(string& fname);
    void writeStationsTest(string& fname);
    void readNetTest(string& fname);
    void writeNetTest(string& fname);
    void writeRoutsListTest(string& fname);
    void readRoutsListTest(string& fname);
    virtual ~JsonExchangerTest();
};
}
#endif /* JSONEXCHANGERTEST_H_ */
