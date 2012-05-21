/*
 * OnlineQueryProcessor.h
 *
 *  Created on: Oct 29, 2011
 *      Author: rohit
 */

#ifndef ONLINEQUERYPROCESSOR_H_
#define ONLINEQUERYPROCESSOR_H_


#include "../DocumentParsers/CWhiteSpaceParser.h"
#include "../include/CUtilities.h"
#include "../Indexer/StringHelper.h"
#include "../QueryRepresentation/CQuery.h"
#include "../Ranker/VectorSpaceModel.h"
#include "../Ranker/booleanModel.h"
#include "../Ranker/BM25.h"


class OnlineQueryProcessor {
public:
	OnlineQueryProcessor();
	~OnlineQueryProcessor();

	bool processQuery(string user_query,string model,int n);
};


#endif /* ONLINEQUERYPROCESSOR_H_ */
