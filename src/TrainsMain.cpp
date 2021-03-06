/*
 * TrainsMain.cpp

 *
 *  Created on: 25 ????. 2016 ?.
 *      Author: mfurkin
 */
#include <algorithm>
#include <iostream>
#include "Station.h"
#include "Scheduler.h"
#include "SchedulerTest.h"
#include "TrainsMain.h"
#include "boost/lexical_cast.hpp"
#include "boost/filesystem.hpp"

using namespace std;
vector<Station> getStations1()
{
    vector<Station> stations(4);
    stations[0] = Station("A",2);
    stations[1] = Station("B",2);
    stations[2] = Station("C",3);
    stations[3] = Station("D",2);
    return stations;
}

vector<Station> getStations2()
{
    vector<Station> stations(4);
    stations[0] = Station("A",2);
    stations[1] = Station("B",2);
    stations[2] = Station("C",1);
    stations[3] = Station("D",2);
    return stations;
}

vector<Station> getStations3()
{
    vector<Station> stations(4);
    stations[0] = Station("A",1);
    stations[1] = Station("B",2);
    stations[2] = Station("C",3);
    stations[3] = Station("D",2);
    return stations;
}

vector<Line> getLines1()
{
    vector<Line> lines(5);
    lines[0] = Line("A","B",10);
    lines[1] = Line("A","D",10);
    lines[2] = Line("A","C",14);
    lines[3] = Line("B","C",10);
    lines[4] = Line("C","D",10);
    return lines;
}


vector<Station>  getStations (string& fname, function<vector<Station>()> defaultDataCreator, JsonExchanger json)
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

vector<Line> getLines (string& fname, function<vector<Line>()> defaultDataCreator, JsonExchanger json)
{
    vector<Line> result(5);
    function<void(TrainObjectCreatingException&)> readError = [](TrainObjectCreatingException&)
	{
	    cout<<"Exception during net config reading\n";
	    assert(false);
	};
    if (json.fileExists(fname))
	result = json.readNet(fname,readError);
    else
    {
	result = defaultDataCreator();
	json.writeNet(fname,result);
    }
    return result;
}

vector<Rout> getRoutes1()
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
}

vector<Rout> getRoutes2()
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
}

vector<Rout> getRoutes3()
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
}

vector<Rout> getRoutes4()
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
}

vector<Rout> getRoutes5()
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
}

vector<Rout> getRoutes6()
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
}

vector<Rout> getRoutes7()
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
}

vector<Rout> getRouts(string& fname, function<vector<Rout>()> defaultDataCreator, JsonExchanger json)
    {
	vector<Rout> result(3);
	function<void(TrainObjectCreatingException&)> readError = [](TrainObjectCreatingException&)
		{
		    cout<<"Exception during routs reading\n";
		    assert(false);
		};
	if (json.fileExists(fname))
	{
	    result = json.readRoutsList(fname,readError);
	}
	else
	{
	    result = defaultDataCreator();
	    json.writeRoutsList(fname,result);
	}
	return result;
    }
void runOneTest(string& testDir,string& testCase, SchedulerTest& test, StationCreatorProcType stationCreator,RoutCreatorProcType routCreator, bool expected_result, string& testName)
{
    string stations_name("stations"),lines_name("net"),routs_name("routs");
    string stations_fname = test.createPath(testDir,stations_name,testCase),lines_fname = test.createPath(testDir,lines_name,testCase), routs_fname = test.createPath(testDir,routs_name,testCase);
    JsonExchanger json;
    vector<Station> stations = getStations(stations_fname,stationCreator,json);
    vector<Line> lines = getLines(lines_fname,getLines1,json);
    vector<Rout> routs = getRouts(routs_fname,routCreator,json);
    test.runTest(stations,lines,routs,expected_result,testName);
}

void showUsage(ParamsType& params)
{
    cout<<"Trains schedule checker. Written by M.Furkin as test.\n";
    cout<<"Usage:\n";
    cout<<"trains -test <testCase> <testDir>                    - runs tests for this utility\n";
    cout<<"\n";
    cout<<"      <testCase> - testcase which should be ran\n";
    cout<<"      <testDir> - directory which contains input data for test. Input data are files which are called <testCase>_stations.txt, <testCase>_net.txt\n";
    cout<<"                  and <testCase>_routs.txt. They contains information about stations net configuration and planned routes respectively.\n";
    cout<<"                  If such files do not exist they will be created during test.\n";
    cout<<"\n";
    cout<<"trains -check <stations_fname> <lines_fname> <routs_fname>                                - checks some schedules for failures \n";
    cout<<"      <stations_fname> - input data about stations for some case which should be checked \n";
    cout<<"      <lines_fname>    - input data about net configuration for some case which should be checked \n";
    cout<<"      <routs_fname> - input data about routs for some case which should be checked \n";
    cout<<"\n";
    cout<<"trains -jsonTest <testType> <dataType> <fname.txt>                            - tests JsonExchanger class \n";
    cout<<"	<testType> - could be \"write\" or \"read\" for file writing or reading tests respectively.\n";
    cout<<" 	<dataType> - coulde be \"stations\", \"net\",  \"routs\" or \"all\" for specified data writing/reading test. Usage for \"all\" see as follows\n";
    cout<<" 	<filename> - file absoluth path for JSON writing/reading test\n";
    cout<<"\n";
    cout<<"trains -jsonTest <testType> <dataType> <stations_fname.txt> <net_fname.txt <routs_fname.txt>\n - tests for all data types\n";
    cout<<"<stations_fname> - absoluth path for file that contains stations information\n";
    cout<<"<net_fname> - absoluth path for file that contains net configuration information\n";
    cout<<"<routs_fname> - absoluth path for file that contains routs information\n";
    cout<<"\n";
    cout<<"All file names should be specified with full absoluth paths\n";
    cout<<"trains -showUsage              - prints this instruction\n";
}

void invalidParamsMessage(ParamsType& params)
{
    cout<<"Invalid parameters specified!!!\n";
    showUsage(params);
}

JsonTestActionMap createJsonWriteActionsMap(string& testType)
{
//  map<string,JsonTestActionProcType> result;
    JsonTestActionMap result;
    result["stations"] = [](string& fname, JsonExchangerTest& jet)
	{
	    jet.writeStationsTest(fname);
	};
    result["net"] = [](string& fname, JsonExchangerTest& jet)
	{
	    jet.writeNetTest(fname);
	};
    result["routs"] = [](string& fname, JsonExchangerTest& jet)
	{
	    jet.writeRoutsListTest(fname);
	};
    return result;
}

JsonTestActionMap createJsonReadActionsMap(string& testType)
{
 // map<string,JsonTestActionProcType> result;
    JsonTestActionMap result;
    result["stations"] = [](string& fname, JsonExchangerTest& jet)
	{
	    jet.readStationsTest(fname);
	};
    result["net"] = [](string& fname, JsonExchangerTest& jet)
	{
	    jet.readNetTest(fname);
	};
    result["routs"] = [](string& fname, JsonExchangerTest& jet)
	{
	    jet.readRoutsListTest(fname);
	};
    return result;
}
JsonTestActionFactoryProcType createJsonActionFactory(string& type)
{
    map<string,JsonTestActionFactoryProcType> storage;
    storage["write"] = createJsonWriteActionsMap;
    storage["read"] = createJsonReadActionsMap;
    return storage[type];
}
void jsonTest(ParamsType& params)
{
    ParamsType::iterator end = params.end(), it;
    it = params.find("jsonTestType");
    if (it == end)
    {
	invalidParamsMessage(params);
    }
    else
    {
	JsonExchangerTest jet;
	string testType = it->second;
	ParamsType::iterator dataTypeIt = params.find("jsonDataType");
	if (dataTypeIt == end)
	{
	    invalidParamsMessage(params);
	}
	else
	{
	    string dataType = dataTypeIt->second;
	    JsonTestActionFactoryProcType factory = createJsonActionFactory(testType);
	    JsonTestActionMap actionsMap = factory(dataType);
	    if (dataType != "all")
	    {
		JsonTestActionProcType proc = actionsMap[dataType];
		ParamsType::iterator fnameIt = params.find("filename");
		if (fnameIt == end)
		    invalidParamsMessage(params);
		else
		    proc(fnameIt->second,jet);
	    }
	    else
	    {
		ParamsType::iterator stationsFnameIt = params.find("stations_fname"),linesFnameIt = params.find("lines_fname"),
				     routsFnameIt = params.find("routs_fname");
		if ((stationsFnameIt == end) || (linesFnameIt == end) || (routsFnameIt == end))
		    invalidParamsMessage(params);
		else
		{
		    JsonTestActionProcType stationsProc = actionsMap["stations"], netProc = actionsMap["net"], routsProc = actionsMap["routs"];
		    stationsProc(stationsFnameIt->second,jet);
		    netProc(linesFnameIt->second,jet);
		    routsProc(routsFnameIt->second,jet);
		}
	    }
	}
    }
}

void runTest(ParamsType& params)
{
    map<string,string>::iterator end = params.end(),testCaseIt,testDirIt;
    string testNames[TEST_CASE_NUM] = { string("test1_failOnLine"),string("test2_failOnStation"),string("test3_OKstartersTooMuch"),string("test4_FailSameLineSameTime"),
			    string("test5_OKFinishersTooMuch"),string("test6_failOnShortRout"),string("test7_OKMeetingOnStation")};
    int index;
    testCaseIt = params.find("testCase");
    testDirIt = params.find("testDir");
    if ((testCaseIt == end) || (testDirIt == end))
	invalidParamsMessage(params);
    else
    {
	SchedulerTest test;
	string testName = testCaseIt->second;
	string testDir = testDirIt->second;
	StationCreatorProcType stationCreators[TEST_CASE_NUM] = {getStations1,getStations2,getStations3,getStations3,getStations3,getStations3,getStations3};
	RoutCreatorProcType routCreators[TEST_CASE_NUM] = {getRoutes1,getRoutes2,getRoutes3,getRoutes4,getRoutes5,getRoutes6,getRoutes7};
	bool expected_results[TEST_CASE_NUM] = {false,false,true,false,true,false,true};
	if (testName == "all")
	{
	    int i;
	    string st,curTestDir,st2;
	    boost::filesystem::path curPath, parentPath(testDir);
	    for (i=0;i<TEST_CASE_NUM;)
	    {
		index = i++;
		st = "test"+boost::lexical_cast<string>(i);
		curPath = parentPath;
		curPath /= st;
		st2 = curPath.string();
		runOneTest(st2,st,test,stationCreators[index],routCreators[index],expected_results[index],testNames[index]);
	    }
	}
	else
	{
	    index = boost::lexical_cast<int>(testName) - 1;
	    string testCase = "test"+testName;
	    runOneTest(testDir,testCase,test,stationCreators[index],routCreators[index],expected_results[index],testNames[index]);
	}
    }
}

void runCheck(ParamsType& params)
{
    ParamsType::iterator stationsFnameIt,linesFnameIt,routsFnameIt,end = params.end();
    stationsFnameIt = params.find("stations_fname");
    linesFnameIt = params.find("lines_fname");
    routsFnameIt = params.find("routs_fname");
    if ((stationsFnameIt == end) || (linesFnameIt == end) || (routsFnameIt == end))
	invalidParamsMessage(params);
    else
    {
	string stationsFname = stationsFnameIt->second,linesFname = linesFnameIt->second,routsFname = routsFnameIt->second;
	JsonExchanger json;
	StationCreatorProcType stationsCreator = []()
	{
	    cout<<"Stations file have not been found\n";
	    return vector<Station>();
	};
	LineCreatorProcType linesCreator = []()
	{
	    cout<<"Net file have not been found\n";
	    return vector<Line>();
	};
	RoutCreatorProcType routsCreator =  []()
	{
	    cout<<"Routs file have not been found\n";
	    return vector<Rout>();
	};
	cout<<"stationsFname="<<stationsFname<<" linesFname="<<linesFname<<" routsFname="<<routsFname<<"\n";
	vector<Station> stations  = getStations(stationsFname,stationsCreator,json);
	vector<Line> lines = getLines(linesFname,linesCreator,json);
	vector<Rout> routs = getRouts(routsFname,routsCreator,json);
	if ((stations.size() == 0) || (lines.size() == 0) ||  (routs.size() == 0))
	    cout<<"Incorrect file name have been specified\n";
	else
	{
	    cout<<"checking started...\n";
	    Scheduler scheduler = Scheduler(stations,lines,routs);
	    bool result = scheduler.schedule();
	    cout<<((result) ? "schedule is correct" : "schedule failed")<<"\n";
	}
    }
}

void parseTest(ParamsType& params, int argc, char** argv)
{
    if (argc>3)
    {
	params["testCase"] = string(argv[2]);
	params["testDir"] = string(argv[3]);
    }
}

void parseCheck(ParamsType& params,int argc, char** argv)
{
    if (argc>4)
    {
	params["stations_fname"] = string(argv[2]);
	params["lines_fname"] = string(argv[3]);
	params["routs_fname"] = string(argv[4]);
    }
}

void parseShowUsage(ParamsType& params, int argc, char** argv)
{

}

void parseJsonTest(ParamsType& params, int argc, char** argv)
{
    if (argc > 3)
    {
	params["jsonTestType"] = string(argv[2]);
	string jsonDataType = string(argv[3]);
	params["jsonDataType"] = jsonDataType;
	if (jsonDataType != "all")
	{
	    if (argc > 4)
		params["filename"] = string(argv[4]);
	}
	else
	    if (argc > 6)
	    {
		params["stations_fname"] = argv[4];
		params["lines_fname"] = argv[5];
		params["routs_fname"] = argv[6];
	    }
    }
}
RunProcType decodeFirstParam(int argc, char** argv, ParamsType& params, map<string,RunProcType> decoder, map<string, ParserProcType> parser)
{
    RunProcType result = invalidParamsMessage;
    map<string,RunProcType>::iterator it,end = decoder.end();
    string firstParam = string(argv[1]);
    it = decoder.find(firstParam);
    if (it != end)
    {
	result = it->second;
	parser[firstParam](params,argc,argv);
    }
    return result;
}

int main(int argc, char** argv)
{
    string TEST_PARAM("-test"),CHECK_PARAM("-check"),SHOW_USAGE_PARAM("-showUsage"),
	   JSON_TEST_PARAM("-jsonTest");
    int result = 0;
    map<string,string> params;
    if (argc == 1)
	invalidParamsMessage(params);
    else
    {
	RunProcType action;
	map<string,RunProcType> actionsByNames;
	RunProcType func;
	string param, param_value;
	map<string, RunProcType> decoder;
	map<string, ParserProcType> parser;
	ParamsType::iterator end,param_it;
	decoder[TEST_PARAM] = runTest;
	decoder[CHECK_PARAM] = runCheck;
	decoder[SHOW_USAGE_PARAM] = showUsage;
	decoder[JSON_TEST_PARAM] = jsonTest;
	parser[TEST_PARAM] = parseTest;
	parser[CHECK_PARAM] = parseCheck;
	parser[SHOW_USAGE_PARAM] = parseShowUsage;
	parser[JSON_TEST_PARAM] = parseJsonTest;
	action = decodeFirstParam(argc,argv,params,decoder,parser);
	action(params);
    }
    return result;
}


