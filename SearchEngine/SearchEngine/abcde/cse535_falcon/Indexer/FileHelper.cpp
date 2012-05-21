/*
 *	File: FileHelper.cpp
 *	Version: 1.0
 *	Desc:
 *	History:
 *	1. 2011-09-12, Created, Jun Wu
 */

#include "FileHelper.h"

FileHelper::FileHelper() {
	// TODO Auto-generated constructor stub

}

FileHelper::~FileHelper() {
	// TODO Auto-generated destructor stub
}

bool FileHelper::writeToFile(string &filePath, string &content){
	bool status = false;
	if (filePath.length() == 0 || content.length() == 0)
		return false;

	ofstream out;
	out.open(filePath.c_str(), ios::out);

	if(!out.good()){
		cout << "File " << filePath << " is not existed!" << filePath << endl;
		return false;
	}

	out << content;
	out.close();
	status = true;
	return status;
}


