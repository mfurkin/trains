/*
 * JsonExchanger.cpp
 *
 *  Created on: 22 ????. 2016 ?.
 *      Author: mfurkin
 */


#include <vector>
#include <fstream>
#include <cstring>
#include <functional>
#include <algorithm>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/allocators.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "JsonExchanger.h"
#include "KeyAlreadyExistsException.h"
namespace std {

JsonExchanger::JsonExchanger()
{
}

void JsonExchanger::writeStations(string& fname, vector<Station> aStations)
{
    ofstream ofstr(fname,ios_base::out | ios_base::trunc);
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value array(rapidjson::kArrayType);
    vector<Station>::iterator it,end = aStations.end();
    rapidjson::OStreamWrapper osw(ofstr);
    rapidjson::Value curVal,obj;
    function<void(rapidjson::Value&, string& name, int waysQty)> funcDataSaver = [&allocator] (rapidjson::Value& anArray, string& name, int waysQty)
    {
	rapidjson::Value curVal(rapidjson::kObjectType);
	curVal.AddMember("name",name,allocator);
	curVal.AddMember("waysQuantity",waysQty,allocator);
	anArray.PushBack(curVal,allocator);
    };
    array.Reserve(aStations.size(),allocator);
    it=aStations.begin();

    for_each(aStations.begin(),aStations.end(), [&array,funcDataSaver] (Station curStation) mutable
    {
	curStation.saveMe(array,funcDataSaver);
    });
    doc.SetObject();
    doc.AddMember("stations",array,allocator);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

vector<Station> JsonExchanger::readStations(string& fname, function<void(TrainObjectCreatingException&)> onKeyAlreadyExists)
{
    list<Station> result;
    string name("stations");
    int i = 0;
    function<void(rapidjson::Value& curVal)> funcDataReader = [&result](rapidjson::Value& curVal)
    {
	result.push_back(Station(curVal["name"].GetString(),curVal["waysQuantity"].GetInt()));
    };
    readArray(fname,funcDataReader,onKeyAlreadyExists,name);
    vector<Station> res2(result.size());
    for_each(result.begin(),result.end(),[&res2,&i](Station& curStation)
    {
	res2[i++] = curStation;
    });
    return res2;
}

void JsonExchanger::readArray(string& fname, function<void(rapidjson::Value&)> onItem, function<void(TrainObjectCreatingException&)> onError, string& name)
{

   rapidjson::Value array;
   ifstream ifstr(fname,ios_base::in);
   rapidjson::IStreamWrapper isw(ifstr);
   rapidjson::Document doc;
   doc.ParseStream(isw);
   array = doc[name];
   int size = array.Size(),i;
   for (i=0;i<size;i++)
       try
       {
	   onItem(array[i]);
       }
       catch(TrainObjectCreatingException& toce)
       {
	   onError(toce);
       }
}

int JsonExchanger::fileExists (string& fname)
{
    ifstream ifstr(fname);
    int result = ifstr.good();
    ifstr.close();
    return result;
}

vector<Line> JsonExchanger::readNet(string& fname, function<void(TrainObjectCreatingException&)> onStationDoesNotExist)
{
    list<Line> result;
    int i = 0;
    string name("lines");
    function<void(rapidjson::Value&)> funcDataReader = [&result](rapidjson::Value& curVal)
    {
	result.push_back(Line(curVal["firstStation"].GetString(),curVal["secondStation"].GetString(),curVal["length"].GetInt()));
    };
    readArray(fname,funcDataReader,onStationDoesNotExist,name);
    vector<Line> res2(result.size());
    for_each(result.begin(),result.end(),[&res2,&i](Line& curLine)
    {
	res2[i++] = curLine;
    });
    return res2;
}

void JsonExchanger::writeNet (string& fname, vector<Line> lines)
{
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value line(rapidjson::kArrayType);
    ofstream ofstr(fname);
    rapidjson::OStreamWrapper osw(ofstr);
    doc.SetObject();
    for_each(lines.begin(), lines.end(), [&array,&allocator] (Line& curLine)
    {
	curLine.saveMe(array,[&allocator](rapidjson::Value& anArray, string& aFirstStation, string& aSecondStation, int aLength)
	{
	    rapidjson::Value cell(rapidjson::kObjectType);
	    cell.AddMember("firstStation",aFirstStation,allocator);
	    cell.AddMember("secondStation",aSecondStation,allocator);
	    cell.AddMember("length",aLength,allocator);
	    anArray.PushBack(cell,allocator);
	});
    });
    doc.AddMember("lines",array,allocator);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

vector<Rout> JsonExchanger::readRoutsList(string fname, function<void(TrainObjectCreatingException&)> onError)
{

	list<Rout> res2;
	string name("routs");
	function<void(rapidjson::Value&)> funcDataReader= [&res2](rapidjson::Value& curVal)
	{
	    rapidjson::Value curArray;
	    int i = 0;
	    time_t time = curVal["startTime"].GetInt();
	    curArray = curVal["rout"].GetArray();
	    vector<string> rout(curArray.Size());
	    for_each(curArray.Begin(),curArray.End(),[&i,&rout](rapidjson::Value& arrValue)
	    {
		rout[i++] = arrValue.GetString();
	    });
	    res2.push_back(Rout(rout,time));
	};
	readArray(fname,funcDataReader,onError,name);
	int size = res2.size();
	vector<Rout> result(size);
	int i = 0;
	for_each(res2.begin(),res2.end(),[&result,&i](Rout& curRout)
	{
	    result[i++] = curRout;
	});
	return result;
}

void JsonExchanger::writeRoutsList(string fname, vector<Rout> aRouts)
{
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value line(rapidjson::kArrayType);
    ofstream ofstr(fname);
    rapidjson::OStreamWrapper osw(ofstr);
    doc.SetObject();
    for_each(aRouts.begin(), aRouts.end(), [&array,&allocator] (Rout& curRout)
    {
	curRout.saveMe(array,[&allocator](rapidjson::Value& array, vector<string>& rout, time_t aTime)
	{
	    rapidjson::Value cell(rapidjson::kObjectType), routArray(rapidjson::kArrayType);
	    cell.AddMember("startTime",(unsigned int)aTime,allocator);
	    for_each(rout.begin(),rout.end(),[&routArray,&allocator](string& curStation)
	    {
		rapidjson::Value routCell(rapidjson::kStringType);
		routCell.SetString(curStation,allocator);
		routArray.PushBack(routCell,allocator);
	    });
	    cell.AddMember("rout",routArray,allocator);
	    array.PushBack(cell,allocator);
	});
    });
    doc.AddMember("routs",array,allocator);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

JsonExchanger::~JsonExchanger()
{
}

} /* namespace std */
