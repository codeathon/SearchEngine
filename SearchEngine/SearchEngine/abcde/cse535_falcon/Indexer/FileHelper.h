/*
 *	File: FileHelper.h
 *	Version: 1.0
 *	Desc:
 *	History:
 *	1. 2011-09-12, Created, Jun Wu
 */

#ifndef FILEHELPER_H_
#define FILEHELPER_H_

#include "../include/includes.h"

using namespace std;

class FileHelper {
public:
	FileHelper();
	virtual ~FileHelper();

	bool static writeToFile(string &filename, string &file_directory);
};

#endif /* FILEHELPER_H_ */
