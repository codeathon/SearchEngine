/*
 *	File: Config.h
 *	Version: 1.0
 *	Desc:
 *	History:
 *	1. 2011-09-26, Created, Jun Wu
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include "../include/includes.h"
#include "StringHelper.h"

using namespace std;

class Config {
public:
	Config();
	Config(string &configFilePath);
	virtual ~Config();

	static multimap<string, string> paras;

	string static getValue(string paraName);
};

#endif /* CONFIG_H_ */
