/*
 *	File: StringHelper.h
 *	Version: 1.0
 *	Desc:
 *	History:
 *	1. 2011-09-12, Created, Jun Wu
 */

#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include "../DocumentRepresentation/CDocument.h"

using namespace std;

class StringHelper {
public:
	StringHelper();
	virtual ~StringHelper();

	void static toLowerCase(string &str);
	string static trim(string src);
	int static toInt(string str);
	size_t toUl(string str);
	vector<string> static split(string str, string delimiters);
};

#endif /* STRINGHELPER_H_ */
