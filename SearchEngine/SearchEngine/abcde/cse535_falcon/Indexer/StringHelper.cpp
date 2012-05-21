/*
 *	File: StringHelper.cpp
 *	Version: 1.0
 *	Desc:
 *	History:
 *	1. 2011-09-12, Created, Jun Wu
 */

#include "StringHelper.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;
StringHelper::StringHelper() {
	// TODO Auto-generated constructor stub

}

StringHelper::~StringHelper() {
	// TODO Auto-generated destructor stub
}

void StringHelper::toLowerCase(string &str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

vector<string> StringHelper::split(string str, string delimiters){
    vector<string> tokens;
	// Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }

	return tokens;
}

string StringHelper::trim(string src){
	string dest = src;
	string delims = "\t\r\n ";

	size_t index = dest.find_first_not_of(delims);

	if(index == string::npos)
		dest.erase();
	else
		dest.erase(0, index);

	return dest;
}

int StringHelper::toInt(string str){
	return atoi(str.c_str());
}
size_t StringHelper:: toUl(string str) {
	istringstream f(str);
	size_t ans;
	f >> ans;
	return ans;
}
