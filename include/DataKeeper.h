/*
 * StationSaver.h
 *
 *  Created on: 8 ???. 2016 ?.
 *      Author: mfurkin
 */

#ifndef STATIONKEEPER_H_
#define STATIONKEEPER_H_
#include <map>
namespace std
{

    class DataKeeper
    {
    private:
	static DataKeeper& keeper;
	map<string, int> dataKeep;
	map<string, int> instanceQtyKeep;
	DataKeeper();
	~DataKeeper ();
    public:
	DataKeeper(const DataKeeper& aKeeper) = delete;
	DataKeeper& operator=(const DataKeeper&) = delete;
	static DataKeeper& getKeeper();
	int exists(string& name);
	void add(string& name, int waysQty);
	void copy(string& name);
	void remove(string& name);
	int getData(const string& name);
    };

} /* namespace std */

#endif /* STATIONKEEPER_H_ */
