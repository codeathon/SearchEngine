/*
 * booleanModel.h
 *
 *  Created on: Oct 29, 2011
 *      Author: nishant
 */

#ifndef BOOLEANMODEL_H_
#define BOOLEANMODEL_H_
#include "../include/CUtilities.h"
#include "../QueryRepresentation/CQuery.h"
#include "../DocumentRepresentation/CDocument.h"
#include "../Indexer/StringHelper.h"

namespace std {

class booleanModel {
public:
	booleanModel();
	virtual ~booleanModel();
	bool get_doc_ids(CQuery* q);
	std::vector<std::string>final_docs;
	std::multimap<int,int>term_id_doc_id;
};

} /* namespace std */
#endif /* BOOLEANMODEL_H_ */
