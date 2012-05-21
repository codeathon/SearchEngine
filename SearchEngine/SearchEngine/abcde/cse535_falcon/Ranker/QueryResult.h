/*
 * QueryResult.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Jun Wu
 */

#ifndef QUERYRESULT_H_
#define QUERYRESULT_H_

#include "../include/includes.h"

using namespace std;

class QueryResult {
public:
	QueryResult();
	virtual ~QueryResult();
	QueryResult(size_t topic, string docName, int uniqNumber, float score);

	size_t topic;
	int iteration;
	string documentName;
	int uniqueNumber;
	float score;
	string comment;

	friend bool operator < (const QueryResult result1, const QueryResult result2)
	{
		if(result1.score < result2.score)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend bool operator == (const QueryResult result1, const QueryResult result2)
	{
		if(result1.score == result2.score)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend bool operator > (const QueryResult result1, const QueryResult result2)
	{
		if(result1.score > result2.score)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};

#endif /* QUERYRESULT_H_ */
