/*
 * CQuery.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: rohit
 */



#include "CQuery.h"


CQuery::CQuery() {

}

CQuery::~CQuery() {

}


void CQuery::setQueryNarr(vector<string> narr) {
	query_narr = narr;
}

void CQuery::setQueryTitle(vector<string> title) {
	query_title = title;
}


void CQuery::setQueryDesc(vector<string> desc) {
	query_desc = desc;
}

size_t CQuery::getLength() const
{
    return length;
}

void CQuery::setLength(size_t length)
{
    this->length = length;
}

vector<string> CQuery::getQtokens() const
{
    return qtokens;
}

void CQuery::setQtokens(vector<string> query_tokens)
{
    qtokens = query_tokens;
}

size_t CQuery::getQueryId() const
{
    return query_id;
}

void CQuery::setQueryId(size_t queryId)
{
    query_id = queryId;
}
