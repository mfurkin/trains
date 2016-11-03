/*
 * SchedulerTest.cpp
 *
 *  Created on: 17 ???. 2016 ?.
 *      Author: mfurkin
 */
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>
#include "JsonExchanger.h"
#include "SchedulerTest.h"
#include "Scheduler.h"

namespace std
{
/*
    string SchedulerTest::TEST1_NAME = string("test1_failOnLine");
    string SchedulerTest::TEST2_NAME = string("test2_failOnStation");
    string SchedulerTest::TEST3_NAME = string("test3_OKstartersTooMuch");
    string SchedulerTest::TEST4_NAME = string("test4_FailSameLineSameTime");
    string SchedulerTest::TEST5_NAME = string("test5_OKFinishersTooMuch");
    string SchedulerTest::TEST6_NAME = string("test6_failOnShortRout");
    string SchedulerTest::TEST7_NAME = string("test7_OKMeetingOnStation");
*/
//  SchedulerTest::SchedulerTest ():json(), readError([](TrainObjectCreatingException& toce)
    SchedulerTest::SchedulerTest ()
    {

    }
/*
    vector<Station>  SchedulerTest::getStations (string& fname, function<vector<Station>()> defaultDataCreator)
    {
	vector<Station> result;
	if (json.fileExists(fname))
		result = json.readStations(fname, [](TrainObjectCreatingException& toce )
			 {
			    cout<<"Exception during stations reading\n";
			    assert(false);
			 });
	else
	{
	    result = defaultDataCreator();
	    json.writeStations(fname,result);
	}
	return result;
    }

    vector<Line> SchedulerTest::getLines (string& fname, function<vector<Line>()> defaultDataCreator)
    {
	vector<Line> result(5);
	if (json.fileExists(fname))
	    result = json.readNet(fname,readError);
	else
	{
	    result = defaultDataCreator();
	    json.writeNet(fname,result);
	}
	return result;
    }

    vector<Rout> SchedulerTest::getRoutsList (string& fname, function<vector<Rout>()> defaultDataCreator)
    {
	vector<Rout> result(3);
	if (json.fileExists(fname))
	    result = json.readRoutsList(fname,readError);
	else
	{
	    result = defaultDataCreator();
	    json.writeRoutsList(fname,result);
	}
	return result;
    }
*/
    void SchedulerTest::runTest (vector<Station> stations, vector<Line> lines, vector<Rout> routs, bool expected_result, string& test_name)
    {
	bool result;
	cout<<"test "<<test_name<<" started\n";
	Scheduler scheduler(stations,lines,routs);
	result = scheduler.schedule();
	cout<<"SchedulerTest::runTest result="<<result<<"\n";
	assert(result==expected_result);
	cout<<"test "<<test_name<<" passed\n";
    }

    SchedulerTest::~SchedulerTest ()
    {

    }
/*
    void  SchedulerTest::test1_failOnLine(string& stations_fname, string& lines_fname, string& routs_fname)
    {
	cout<<"test1 enter\n";
	vector<Station> stations(4);
        vector<Line> lines(5);
        vector<Rout> routs(3);
        function<vector<Station>()> stationsCreator = []()-> vector<Station>
        {
            vector<Station> stations(4);
            stations[0] = Station("A",2);
            stations[1] = Station("B",2);
            stations[2] = Station("C",3);
            stations[3] = Station("D",2);
	    return stations;
        };
        stations = getStations(stations_fname,stationsCreator);
        function<vector<Line>()> linesCreator = []()-> vector<Line>
        {
            vector<Line> lines(5);
            lines[0] = Line("A","B",10);
            lines[1] = Line("A","D",10);
            lines[2] = Line("A","C",14);
            lines[3] = Line("B","C",10);
            lines[4] = Line("C","D",10);
            return lines;
        };

        lines = getLines(lines_fname,linesCreator);
        function<vector<Rout>()> routsCreator = []() -> vector<Rout>
        {
            vector<string> rout0 = {"A","B","C","D"};
            vector<string> rout1 = {"A","C","D"};
            vector<string> rout2 = {"A","D","C"};
            vector<Rout> routs(3);
            time_t st_0,st_1,st_2;
            st_0 = time(NULL);
            st_1 = st_0 + 10;
            st_2 = st_0 + 15;
            routs[0] = Rout(rout0,st_0);
            routs[1] = Rout(rout1,st_1);
            routs[2] = Rout(rout2,st_2);
            return routs;
        };
        routs = getRoutsList(routs_fname,routsCreator);
        runTest(stations,lines,routs,false,TEST1_NAME);
    }

    void SchedulerTest::test2_failOnStation(string& stations_fname, string& lines_fname, string& routs_fname)
    {
	vector<Station> stations(4);
	vector<Line> lines(5);
	vector<Rout> routs(3);

	function<vector<Station>()> stationsCreator = []()->vector<Station>
	{
	    vector<Station> stations(4);
	    stations[0] = Station("A",2);
	    stations[1] = Station("B",2);
	    stations[2] = Station("C",1);
	    stations[3] = Station("D",2);
	    return stations;
	};
	stations = getStations(stations_fname,stationsCreator);

	function<vector<Line>()> linesCreator = []()-> vector<Line>
	        {
	            vector<Line> lines(5);
	            lines[0] = Line("A","B",10);
	            lines[1] = Line("A","D",10);
	            lines[2] = Line("A","C",14);
	            lines[3] = Line("B","C",10);
	            lines[4] = Line("C","D",10);
	            return lines;
	        };
	lines = getLines(lines_fname,linesCreator);

        function<vector<Rout>()> routsCreator = []() -> vector<Rout>
        {
            vector<string> rout0 = {"A","B","C","D"};
            vector<string> rout1 = {"A","C","D"};
            vector<string> rout2 = {"A","D","C"};
            vector<Rout> routs(3);
            time_t st_0,st_1,st_2;
            st_0 = time(NULL);
            st_1 = st_0 + 6;
            st_2 = st_0 + 15;
            routs[0] = Rout(rout0,st_0);
            routs[1] = Rout(rout1,st_1);
            routs[2] = Rout(rout2,st_2);
            return routs;
        };
	routs = getRoutsList(routs_fname,routsCreator);
	runTest(stations,lines,routs,false,TEST2_NAME);
    }

    void SchedulerTest::test3_OKstartersTooMuch(string& stations_fname, string& lines_fname, string& routs_fname)
    {
	vector<Station> stations(4);
	vector<Line> lines(5);
	vector<Rout> routs(3);
	function<vector<Station>()> stationsCreator = []()->vector<Station>
	{
	    vector<Station> stations(4);
	    stations[0] = Station("A",1);
	    stations[1] = Station("B",2);
	    stations[2] = Station("C",3);
	    stations[3] = Station("D",2);
	    return stations;
	};
	stations = getStations(stations_fname,stationsCreator);
	function<vector<Line>()> linesCreator = []()-> vector<Line>
	{
	    vector<Line> lines(5);
	    lines[0] = Line("A","B",10);
	    lines[1] = Line("A","D",10);
	    lines[2] = Line("A","C",14);
	    lines[3] = Line("B","C",10);
	    lines[4] = Line("C","D",10);
	    return lines;
	};
	lines = getLines(lines_fname,linesCreator);
	function<vector<Rout>()> routsCreator = []() -> vector<Rout>
	{
	    vector<string> rout0 = {"A","B","C","D"};
	    vector<string> rout1 = {"A","C","D"};
	    vector<string> rout2 = {"A","D","C"};
	    vector<Rout> routs(3);
	    time_t st_0,st_1,st_2;
	    st_0 = time(NULL);
	    st_1 = st_0 + 10;
	    st_2 = st_0 + 30;
	    routs[0] = Rout(rout0,st_0);
	    routs[1] = Rout(rout1,st_1);
	    routs[2] = Rout(rout2,st_2);
	    return routs;
	};
	routs = getRoutsList(routs_fname,routsCreator);
	runTest(stations,lines,routs,true,TEST3_NAME);
    }

    void SchedulerTest::test4_FailSameLineSameTime(string& stations_fname, string& lines_fname, string& routs_fname)
    {
	vector<Station> stations(4);
	vector<Line> lines(5);
	vector<Rout> routs(3);
	function<vector<Station>()> stationsCreator = []()->vector<Station>
	{
	    vector<Station> stations(4);
	    stations[0] = Station("A",1);
	    stations[1] = Station("B",2);
	    stations[2] = Station("C",3);
	    stations[3] = Station("D",2);
	    return stations;
	};
	stations = getStations(stations_fname,stationsCreator);
	function<vector<Line>()> linesCreator = []()-> vector<Line>
	{
	    vector<Line> lines(5);
	    lines[0] = Line("A","B",10);
	    lines[1] = Line("A","D",10);
	    lines[2] = Line("A","C",14);
	    lines[3] = Line("B","C",10);
	    lines[4] = Line("C","D",10);
	    return lines;
	};
	lines = getLines(lines_fname,linesCreator);
	function<vector<Rout>()> routsCreator = []() -> vector<Rout>
	{
	    vector<string> rout0 = {"A","B","C","D"};
	    vector<string> rout1 = {"A","C","D"};
	    vector<string> rout2 = {"A","D","C"};
	    vector<Rout> routs(3);
	    time_t st_0,st_1,st_2;
	    st_0 = time(NULL);
	    st_1 = st_0 + 6;
	    st_2 = st_0 + 20;
	    routs[0] = Rout(rout0,st_0);
	    routs[1] = Rout(rout1,st_1);
	    routs[2] = Rout(rout2,st_2);
	    return routs;
	};
	routs = getRoutsList(routs_fname,routsCreator);
	runTest(stations,lines,routs,false,TEST4_NAME);

    }

    void SchedulerTest::test5_OKFinishersTooMuch(string& stations_fname, string& lines_fname, string& routs_fname)
    {
	vector<Station> stations(4);
	vector<Line> lines(5);
	vector<Rout> routs(3);
	function<vector<Station>()> stationsCreator = []()->vector<Station>
	{
	    vector<Station> stations(4);
	    stations[0] = Station("A",1);
	    stations[1] = Station("B",2);
	    stations[2] = Station("C",3);
	    stations[3] = Station("D",2);
	    return stations;
	};
	stations = getStations(stations_fname,stationsCreator);
	function<vector<Line>()> linesCreator = []()-> vector<Line>
	{
	    vector<Line> lines(5);
	    lines[0] = Line("A","B",10);
	    lines[1] = Line("A","D",10);
	    lines[2] = Line("A","C",14);
	    lines[3] = Line("B","C",10);
	    lines[4] = Line("C","D",10);
	    return lines;
	};
	lines = getLines(lines_fname,linesCreator);
	function<vector<Rout>()> routsCreator = []() -> vector<Rout>
	{
	    vector<string> rout0 = {"A","B","C"};
	    vector<string> rout1 = {"A","C"};
	    vector<string> rout2 = {"A","D","C"};
	    vector<Rout> routs(3);
	    time_t st_0,st_1,st_2;
	    st_0 = time(NULL);
	    st_1 = st_0 + 6;
	    st_2 = st_0;
	    routs[0] = Rout(rout0,st_0);
	    routs[1] = Rout(rout1,st_1);
	    routs[2] = Rout(rout2,st_2);
	    return routs;
	};
	routs = getRoutsList(routs_fname,routsCreator);
	runTest(stations,lines,routs,true,TEST5_NAME);
    }

    void SchedulerTest::test6_failOnShortRout (string& stations_fname, string& lines_fname, string& routs_fname)
    {
	vector<Station> stations(4);
	vector<Line> lines(5);
	vector<Rout> routs(3);
	function<vector<Station>()> stationsCreator = []()->vector<Station>
	{
	    vector<Station> stations(4);
	    stations[0] = Station("A",1);
	    stations[1] = Station("B",2);
	    stations[2] = Station("C",3);
	    stations[3] = Station("D",2);
	    return stations;
	};
	stations = getStations(stations_fname,stationsCreator);
	function<vector<Line>()> linesCreator = []()-> vector<Line>
	{
	    vector<Line> lines(5);
	    lines[0] = Line("A","B",10);
	    lines[1] = Line("A","D",10);
	    lines[2] = Line("A","C",14);
	    lines[3] = Line("B","C",10);
	    lines[4] = Line("C","D",10);
	    return lines;
	};
	lines = getLines(lines_fname,linesCreator);
	function<vector<Rout>()> routsCreator = []() -> vector<Rout>
	{
	    vector<string> rout0 = {"A","B"};
	    vector<string> rout1 = {"B","A"};
	    vector<string> rout2 = {"A","D","C"};
	    vector<Rout> routs(3);
	    time_t st_0,st_1,st_2;
	    st_0 = time(NULL);
	    st_1 = st_0 + 6;
	    st_2 = st_0 +10;
	    routs[0] = Rout(rout0,st_0);
	    routs[1] = Rout(rout1,st_1);
	    routs[2] = Rout(rout2,st_2);
	    return routs;
	};
	routs = getRoutsList(routs_fname,routsCreator);
	runTest(stations,lines,routs,false,TEST6_NAME);
    }
    void SchedulerTest::test7_OKMeetingOnStation (string& stations_fname, string& lines_fname, string& routs_fname)
    {
	vector<Station> stations(4);
	vector<Line> lines(5);
	vector<Rout> routs(3);
	function<vector<Station>()> stationsCreator = []()->vector<Station>
	{
	    vector<Station> stations(4);
	    stations[0] = Station("A",1);
	    stations[1] = Station("B",2);
	    stations[2] = Station("C",3);
	    stations[3] = Station("D",2);
	    return stations;
	};
	stations = getStations(stations_fname,stationsCreator);
	function<vector<Line>()> linesCreator = []()-> vector<Line>
	{
	    vector<Line> lines(5);
	    lines[0] = Line("A","B",10);
	    lines[1] = Line("A","D",10);
	    lines[2] = Line("A","C",14);
	    lines[3] = Line("B","C",10);
	    lines[4] = Line("C","D",10);
	    return lines;
	};
	lines = getLines(lines_fname,linesCreator);
	function<vector<Rout>()> routsCreator = []() -> vector<Rout>
	{
	    vector<string> rout0 = {"B","C","D"};
	    vector<string> rout1 = {"A","C","B"};
	    vector<string> rout2 = {"D","C","A"};
	    vector<Rout> routs(3);
	    time_t st_0,st_1,st_2;
	    st_1 = time(NULL);
	    st_0 = st_1 + 4;
	    st_2 = st_1 + 4;
	    routs[0] = Rout(rout0,st_0);
	    routs[1] = Rout(rout1,st_1);
	    routs[2] = Rout(rout2,st_2);
	    return routs;
	};
	routs = getRoutsList(routs_fname,routsCreator);
	runTest(stations,lines,routs,true,TEST7_NAME);
    }
*/
    string SchedulerTest::createFName (string& name, string& testName)
    {
	return testName + "_" + name + ".txt";
    }

    string SchedulerTest::createPath (string& testDir, string& name, string& testName)
    {
	boost::filesystem::path path(testDir);
	string result;
	string fname = createFName(name,testName);
	path /= fname;
	result = path.string();
	return result;
    }
/*
    void SchedulerTest::prepareFileNames(string& testDir, string& testName, string& stations_fname, string& lines_fname, string& routs_fname)
    {
	static string stations_name("stations"),lines_name("lines"),routs_name("routs");
	stations_fname = createPath(testDir,stations_name,testName);
	lines_fname = createPath(testDir,lines_name,testName);
	routs_fname = createPath(testDir,routs_name,testName);
    }

    void SchedulerTest::testAll (string& testDir)
    {
	string stations_fname,lines_fname,routs_fname;
	prepareFileNames(testDir,TEST1_NAME,stations_fname,lines_fname,routs_fname);
	test1_failOnLine(stations_fname,lines_fname,routs_fname);
	prepareFileNames(testDir,TEST2_NAME,stations_fname,lines_fname,routs_fname);
	test2_failOnStation(stations_fname,lines_fname,routs_fname);
	prepareFileNames(testDir,TEST3_NAME,stations_fname,lines_fname,routs_fname);
	test3_OKstartersTooMuch(stations_fname,lines_fname,routs_fname);
	prepareFileNames(testDir,TEST4_NAME,stations_fname,lines_fname,routs_fname);
	test4_FailSameLineSameTime(stations_fname,lines_fname,routs_fname);
	prepareFileNames(testDir,TEST5_NAME,stations_fname,lines_fname,routs_fname);
	test5_OKFinishersTooMuch(stations_fname,lines_fname,routs_fname);
	prepareFileNames(testDir,TEST6_NAME,stations_fname,lines_fname,routs_fname);
	test6_failOnShortRout(stations_fname,lines_fname,routs_fname);
	prepareFileNames(testDir,TEST7_NAME,stations_fname,lines_fname,routs_fname);
	test7_OKMeetingOnStation(stations_fname,lines_fname,routs_fname);
    }
*/
} /* namespace std */


