/*
 * SchedulerTest.cpp
 *
 *  Created on: 17 ???. 2016 ?.
 *      Author: mfurkin
 */

#include <iostream>
#include <vector>
#include "JsonExchanger.h"
#include "SchedulerTest.h"
#include "Scheduler.h"

namespace std
{

    SchedulerTest::SchedulerTest ():json(), readError([](TrainObjectCreatingException& toce)
					    {
						assert(false);
					    })
    {

    }

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

    SchedulerTest::~SchedulerTest ()
    {

    }

    void SchedulerTest::test1_failOnLine ()
    {
	int result;
	cout<<"test1 enter\n";
	vector<Station> stations(4);
        string stations_fname("D:\\tmp3\\test1\\test1_stations.txt");
        vector<Line> lines(5);
        string lines_fname("D:\\tmp3\\test1\\test1_net.txt");
        vector<Rout> routs(3);
        string routs_fname("D:\\tmp3\\test1\\test1_routs.txt");
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

        Scheduler scheduler(stations,lines,routs);
        result = scheduler.schedule();

        cout<<"test1 exit result="<<result<<"\n";
        assert(result==false);
    }
    void SchedulerTest::test2_failOnStation ()
    {
	int result;
	vector<Station> stations(4);

	string stations_fname("D:\\tmp3\\test2\\test2_stations.txt");
	vector<Line> lines(5);
	string lines_fname("D:\\tmp3\\test2\\test2_net.txt");
	vector<Rout> routs(3);
	string routs_fname("D:\\tmp3\\test2\\test2_routs.txt");

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

	Scheduler scheduler(stations,lines,routs);

	result = scheduler.schedule();
	cout<<"test2 exit result="<<result<<"\n";
	assert(result==false);
    }

    void SchedulerTest::test3_OKstartersTooMuch ()
    {
	int result;
	vector<Station> stations(4);
	string stations_fname("D:\\tmp3\\test3\\test3_stations.txt");
	vector<Line> lines(5);
	string lines_fname("D:\\tmp3\\test3\\test3_net.txt");
	vector<Rout> routs(3);
	string routs_fname("D:\\tmp3\\test3\\test3_routs.txt");
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
	Scheduler scheduler(stations,lines,routs);
	result = scheduler.schedule();
	cout<<"test3 exit result="<<result<<"\n";
	assert(result==true);
    }
    void SchedulerTest::test4_FailSameLineSameTime ()
    {
	int result;
	vector<Station> stations(4);
	string stations_fname("D:\\tmp3\\test4\\test4_stations.txt");
	vector<Line> lines(5);
	string lines_fname("D:\\tmp3\\test4\\test4_net.txt");
	vector<Rout> routs(3);
	string routs_fname("D:\\tmp3\\test4\\test4_routs.txt");
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
	Scheduler scheduler(stations,lines,routs);
	result = scheduler.schedule();
	cout<<"test4 exit result="<<result<<"\n";
	assert(result==false);
    }

    void SchedulerTest::test5_OKFinishersTooMuch ()
    {
	int result;
	vector<Station> stations(4);
	string stations_fname("D:\\tmp3\\test5\\test5_stations.txt");
	vector<Line> lines(5);
	string lines_fname("D:\\tmp3\\test5\\test5_net.txt");
	vector<Rout> routs(3);
	string routs_fname("D:\\tmp3\\test5\\test5_routs.txt");
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
	Scheduler scheduler(stations,lines,routs);
	result = scheduler.schedule();
	cout<<"test5 exit result="<<result<<"\n";
	assert(result==true);
    }
    void SchedulerTest::test6_failOnShortRout ()
    {
	int result;
	vector<Station> stations(4);
	string stations_fname("D:\\tmp3\\test6\\test6_stations.txt");
	vector<Line> lines(5);
	string lines_fname("D:\\tmp3\\test6\\test6_net.txt");
	vector<Rout> routs(3);
	string routs_fname("D:\\tmp3\\test6\\test6_routs.txt");
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
	Scheduler scheduler(stations,lines,routs);
	result = scheduler.schedule();
	cout<<"test6 exit result="<<result<<"\n";
	assert(result==false);
    }
    void SchedulerTest::test7_OKMeetingOnStation ()
    {
	int result;
	vector<Station> stations(4);
	string stations_fname("D:\\tmp3\\test7\\test7_stations.txt");
	vector<Line> lines(5);
	string lines_fname("D:\\tmp3\\test7\\test7_net.txt");
	vector<Rout> routs(3);
	string routs_fname("D:\\tmp3\\test7\\test7_routs.txt");
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
	Scheduler scheduler(stations,lines,routs);
	result = scheduler.schedule();
	cout<<"test7 exit result="<<result<<"\n";
	assert(result==true);
    }
    void SchedulerTest::testAll ()
    {
	test1_failOnLine();
	test2_failOnStation();
	test3_OKstartersTooMuch();
	test4_FailSameLineSameTime();
	test5_OKFinishersTooMuch();
	test6_failOnShortRout();
	test7_OKMeetingOnStation();
    }
} /* namespace std */

