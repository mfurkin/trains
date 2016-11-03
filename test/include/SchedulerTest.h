/*
 * SchedulerTest.h
 *
 *  Created on: 17 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef SCHEDULERTEST_H_
#define SCHEDULERTEST_H_
#include <functional>
#include <vector>
#include "JsonExchanger.h"
namespace std
{

    class SchedulerTest
    {
    private:
/*
	static string TEST1_NAME,TEST2_NAME,TEST3_NAME,TEST4_NAME,TEST5_NAME,TEST6_NAME,TEST7_NAME;
	JsonExchanger json;

	vector<Station> getStations(string& fname, function<vector<Station>()> defaultDataCreator);
	vector<Line> getLines(string& fname, function<vector<Line>()> defaultDataCreator);
	vector<Rout> getRoutsList(string& fname, function<vector<Rout>()> defaultDataCreator);
	function<void(TrainObjectCreatingException& toce)> readError;
	void prepareFileNames(string& testDir, string& testName, string& stations_fname, string& lines_fname, string& routs_fname);
*/
    public:
	SchedulerTest ();
	string createFName(string& name, string& testName);
	string createPath(string& testDir, string& name, string& testName);
	void runTest(vector<Station> stations, vector<Line> lines, vector<Rout> routs, bool expected_result, string& test_name);
/*
	void test1_failOnLine(string& stations_fname, string& lines_fname, string& routs_fname);
	void test2_failOnStation(string& stations_fname, string& lines_fname, string& routs_fname);
	void test3_OKstartersTooMuch(string& stations_fname, string& lines_fname, string& routs_fname);
	void test4_FailSameLineSameTime(string& stations_fname, string& lines_fname, string& routs_fname);
	void test5_OKFinishersTooMuch(string& stations_fname, string& lines_fname, string& routs_fname);
	void test6_failOnShortRout(string& stations_fname, string& lines_fname, string& routs_fname);
	void test7_OKMeetingOnStation(string& stations_fname, string& lines_fname, string& routs_fname);
	void testAll(string& testDir);
*/
	virtual	~SchedulerTest ();
    };

} /* namespace std */

#endif /* SCHEDULERTEST_H_ */
