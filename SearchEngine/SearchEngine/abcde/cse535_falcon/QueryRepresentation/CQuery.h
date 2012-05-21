/*
 * CQuery.h
 *
 *  Created on: Oct 27, 2011
 *      Author: rohit
 */

#ifndef CQUERY_H_
#define CQUERY_H_

#include "../include/includes.h"

using namespace std;

class CQuery	{

public:
	size_t query_id;
	size_t length;
	vector<string> query_title;
	vector<string> query_narr;
	vector<string> query_desc;
	vector<string> qtokens; 			// This will be the bag of words
    size_t getLength() const;
    vector<string> getQtokens() const;
    vector<string> getQueryDesc() const;
    size_t getQueryId() const;
    vector<string> getQueryNarr() const;
    vector<string> getQueryTitle() const;
    void setLength(size_t length);
    void setQtokens(vector<string> qtokens);
    void setQueryDesc(vector<string> queryDesc);
    void setQueryId(size_t queryId);
    void setQueryNarr(vector<string> queryNarr);
    void setQueryTitle(vector<string> queryTitle);

	CQuery();
	~CQuery();
};




#endif /* CQUERY_H_ */
