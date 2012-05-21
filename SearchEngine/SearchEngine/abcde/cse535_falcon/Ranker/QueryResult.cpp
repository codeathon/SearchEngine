/*
 * QueryResult.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: Jun Wu
 */

#include "QueryResult.h"

QueryResult::QueryResult() {
	// TODO Auto-generated constructor stub

}

QueryResult::~QueryResult() {
	// TODO Auto-generated destructor stub
}

QueryResult::QueryResult(size_t topic, string docName, int uniqNumber, float score){
	this->topic = topic;
	this->iteration = 0;
	this->documentName = docName;
	this->uniqueNumber = uniqueNumber;
	this->score = score;
	this->comment = "backrub";
}
