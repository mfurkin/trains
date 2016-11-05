/*
 * JsonExchanger.h
 *
 *  Created on: 22 ????. 2016 ?.
 *      Author: mfurkin
 */

#ifndef JSONEXCHANGER_H_
#define JSONEXCHANGER_H_

#include <functional>
#include <list>
#include <string>
#include <vector>
#include "Line.h"
#include "Rout.h"
#include "Saveable.h"
#include "TrainObjectCreatingException.h"
#define TRAINS_DEBUG

namespace std {
class Station;
} /* namespace std */

namespace std {

class JsonExchanger {
public:
    JsonExchanger();
    int fileExists(string& fname);
    void writeStations(string& fname, vector<Station>& aStations);
    void writeArray(string& fname, vector<Saveable*>& savedArray, string& arrayName);
    void readArray(string& fname, function<void(rapidjson::Value&)> onItem, function<void(TrainObjectCreatingException&)> onError, string& name);
    vector<Station> readStations(string&fname, function<void(TrainObjectCreatingException&)> onKeyAlreadyExists);
    vector<Line> readNet(string& fname, function<void(TrainObjectCreatingException&)> onStationDoesNotExist);
    void writeNet(string& fname, vector<Line>);
    vector<Rout> readRoutsList(string fname, function<void(TrainObjectCreatingException&)> onError);
    void writeRoutsList(string fname, vector<Rout> aRouts);
    virtual ~JsonExchanger();
};

} /* namespace std */

#endif /* JSONEXCHANGER_H_ */
