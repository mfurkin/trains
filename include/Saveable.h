/*
 * Saveable.h
 *
 *  Created on: 3 ????. 2016 ?.
 *      Author: mfurkin
 */

#ifndef SAVEABLE_H_
#define SAVEABLE_H_
#include <functional>
namespace std
{
typedef function<void(string& name, int& data)> IntSaver;
typedef function<void(string&name, string& data)> StringSaver;
    class Saveable
    {
    public:
	Saveable ();
	void saveMe(IntSaver anIntSaver, StringSaver aStringSaver);
	virtual	~Saveable ();
    };

} /* namespace std */

#endif /* SAVEABLE_H_ */
