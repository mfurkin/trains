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
namespace std
{
    const int TEST_CASE_NUM = 7;
    typedef map<string,string> ParamsType;
    typedef function<void(ParamsType& params)> RunProcType;
    typedef function<void(ParamsType& params, int argc, char** argv)> ParserProcType;
    typedef function<vector<Station>()> StationCreatorProcType;
    typedef function<vector<Rout>()> RoutCreatorProcType;
}




#endif /* INCLUDE_TRAINSMAIN_H_ */
