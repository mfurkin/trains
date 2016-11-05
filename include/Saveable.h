/*
 * Saveable.h
 *
 *  Created on: 3 ????. 2016 ?.
 *      Author: mfurkin
 */

#ifndef SAVEABLE_H_
#define SAVEABLE_H_
#include <functional>
#include <vector>
namespace std
{
typedef function<void(string& name, int data)> IntSaver;
typedef function<void(string&name, string& data)> StringSaver;
typedef function<void(string& name, vector<string>& data)> StringArraySaver;
    class Saveable
    {
    public:
	Saveable ();
	virtual void saveMe(IntSaver anIntSaver, StringSaver aStringSaver, StringArraySaver aStrArrSaver) = 0;
	virtual	~Saveable ();
    };

} /* namespace std */

#endif /* SAVEABLE_H_ */
