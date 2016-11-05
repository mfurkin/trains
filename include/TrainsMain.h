/*
 * TrainsMain.h
 *
 *  Created on: 2 ????. 2016 ?.
 *      Author: mfurkin
 */

#ifndef INCLUDE_TRAINSMAIN_H_
#define INCLUDE_TRAINSMAIN_H_
#include <functional>
#include <map>
#include "JsonExchangerTest.h"
namespace std
{
    const int TEST_CASE_NUM = 7;
    typedef map<string,string> ParamsType;
    typedef function<void(ParamsType& params)> RunProcType;
    typedef function<void(ParamsType& params, int argc, char** argv)> ParserProcType;
    typedef function<vector<Station>()> StationCreatorProcType;
    typedef function<vector<Line>()> LineCreatorProcType;
    typedef function<vector<Rout>()> RoutCreatorProcType;
    typedef function<void(string&, JsonExchangerTest&)> JsonTestActionProcType;
    typedef map<string,JsonTestActionProcType> JsonTestActionMap;
    typedef function<JsonTestActionMap(string&)> JsonTestActionFactoryProcType;
}




#endif /* INCLUDE_TRAINSMAIN_H_ */
