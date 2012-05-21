/*
 * query.h
 *
 *  Created on: Oct 29, 2011
 *      Author: nishant
 */

#ifndef QUERY_H_
#define QUERY_H_
#include "../include/includes.h"
#include "../include/CUtilities.h"
#include "../Indexer/StringHelper.h"
#include "../QueryRepresentation/CQuery.h"
#include "../Ranker/booleanModel.h"
#include "../TokenProcessor/CBasicTokenProcessor.h"
namespace std {

class query {
public:
	query();

bool prcs_trec_file(string batch_file_path);
	virtual ~query();
};

} /* namespace std */
#endif /* QUERY_H_ */
