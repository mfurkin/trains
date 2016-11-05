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
void JsonExchanger::writeArray (string& fname, vector<Saveable*>& savedArray, string& arrayName)
{
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    ofstream ofstr(fname,ios_base::out | ios_base::trunc);
    rapidjson::OStreamWrapper osw(ofstr);
    array.Reserve(savedArray.size(),allocator);
    for(Saveable* ptr : savedArray)
    {
	rapidjson::Value value(rapidjson::kObjectType);
	printf("writeArray ptr=%x\n",ptr);
	ptr->saveMe([&allocator,&value](string& name, int data)
	{
	    value.AddMember(rapidjson::StringRef(name),data,allocator);
	},
	[&allocator,&value](string& name, string& data)
	{
	    value.AddMember(rapidjson::StringRef(name),data,allocator);
	},
	[&allocator,&value](string& name, vector<string>& data)
	{
	    rapidjson::Value routArray(rapidjson::kArrayType);
	    for_each(data.begin(),data.end(),[&routArray,&allocator](string& curStation)
	    {
	    	rapidjson::Value routCell(rapidjson::kStringType);
	  	routCell.SetString(curStation,allocator);
	  	routArray.PushBack(routCell,allocator);
	    });
	    value.AddMember(rapidjson::StringRef(name),routArray,allocator);
	});
	array.PushBack(value,allocator);
    }
    document.SetObject();
    document.AddMember(rapidjson::StringRef(arrayName),array,allocator);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    document.Accept(writer);
}

void JsonExchanger::writeStations(string& fname, vector<Station>& aStations)
{
    int size = aStations.size();
    vector<Saveable*> savedArr(size);
    string stationsName("stations");
    int i;
    for (i=0;i<size;i++)
	savedArr[i] = &aStations[i];
    writeArray(fname,savedArr,stationsName);
}

vector<Station> JsonExchanger::readStations(string& fname, function<void(TrainObjectCreatingException&)> onKeyAlreadyExists)
{
    list<Station> result;
    string name("stations");
    int i = 0;
    function<void(rapidjson::Value& curVal)> funcDataReader = [&result](rapidjson::Value& curVal)
    {
	int waysQty;
	string name = curVal[Station::NAME_FIELD_NAME].GetString();
	waysQty = curVal[Station::WAYS_QTY_FIELD_NAME].GetInt();
	result.push_back(Station(name,waysQty));
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
    int size = lines.size();
    vector<Saveable*> savedArr(size);
    string linesName("lines");
    int i;
    for (i=0;i<size;i++)
	savedArr[i] = &lines[i];
    writeArray(fname,savedArr,linesName);
}

vector<Rout> JsonExchanger::readRoutsList(string fname, function<void(TrainObjectCreatingException&)> onError)
{

	list<Rout> res2;
	string name("routs");
	function<void(rapidjson::Value&)> funcDataReader= [&res2](rapidjson::Value& curVal)
	{
	    rapidjson::Value curArray;
	    int i = 0,size;
	    time_t time = curVal["startTime"].GetInt();
	    curArray = curVal["rout"].GetArray();
	    size = curArray.Size();
	    vector<string> rout(size);
	    for_each(curArray.Begin(),curArray.End(),[&i,&rout](rapidjson::Value& arrValue)
	    {
		string st = arrValue.GetString();
		rout[i++] = st;
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
    int size = aRouts.size();
    vector<Saveable*> savedArr(size);
    string routsName("routs");
    int i;
    for (i=0;i<size;i++)
	savedArr[i] = &aRouts[i];
    writeArray(fname,savedArr,routsName);
}

JsonExchanger::~JsonExchanger()
{
}

} /* namespace std */
