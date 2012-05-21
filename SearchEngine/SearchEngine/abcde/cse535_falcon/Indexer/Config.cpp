/*
 *	File: Config.cpp
 *	Version: 1.0
 *	Desc:
 *	History:
 *	1. 2011-09-26, Created, Jun Wu
 */

#include "Config.h"
#include "StringHelper.h"

multimap<string, string> Config::paras;

Config::Config() {
	// TODO Auto-generated constructor stub

}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

Config::Config(string &configFilePath){
	string oneLine;
	string paraName;
	string paraValue;

	ifstream configFile(configFilePath.c_str());
	while(!configFile.eof()){
		getline(configFile, oneLine);
		oneLine = StringHelper::trim(oneLine);

		if(oneLine.length()==0)	continue;
		if(oneLine.find_first_of('#')==0)	continue;

		int equalIndex = oneLine.find('=');
		paraName = StringHelper::trim(oneLine.substr(0, equalIndex));
		paraValue = StringHelper::trim(oneLine.substr(equalIndex+1));

		//cout << "paraName:" << paraName << endl;
		//cout << "paraValue:" << paraValue << endl;

		paras.insert(pair<string, string>(paraName, paraValue));
	}
}


string Config::getValue(string paraName){
	string dest;
	map<string, string>::iterator it;
	it = paras.find(StringHelper::trim(paraName));
	if(it!=paras.end()){
		dest = it->second;
	}else{
		cout << "Could not find parameter " << paraName << endl;
	}

	return dest;
}
