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
	JsonExchanger json;
	vector<Station> getStations(string& fname, function<vector<Station>()> defaultDataCreator);
	vector<Line> getLines(string& fname, function<vector<Line>()> defaultDataCreator);
	vector<Rout> getRoutsList(string& fname, function<vector<Rout>()> defaultDataCreator);
	function<void(TrainObjectCreatingException& toce)> readError;
    public:
	SchedulerTest ();
	void test1_failOnLine();
	void test2_failOnStation();
	void test3_OKstartersTooMuch();
	void test4_FailSameLineSameTime();
	void test5_OKFinishersTooMuch();
	void test6_failOnShortRout();
	void test7_OKMeetingOnStation();
	void testAll();
	virtual	~SchedulerTest ();
    };

} /* namespace std */

#endif /* SCHEDULERTEST_H_ */
