/*
 * BM25.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Jun Wu
 */

#ifndef BM25_H_
#define BM25_H_

#include "../include/includes.h"
#include "../QueryRepresentation/CQuery.h"
#include "../DocumentRepresentation/CDocument.h"
#include "../Indexer/Config.h"
#include "../Indexer/StringHelper.h"
#include "../include/CUtilities.h"
#include "QueryResult.h"

#include <math.h>

using namespace std;

class BM25 {
public:
	BM25();
	virtual ~BM25();
	BM25(CQuery *query);

	bool documents_rank(CQuery *query, size_t n);
	static map<string, float> doc_score_map;
	static int top_k;

};

#endif /* BM25_H_ */
