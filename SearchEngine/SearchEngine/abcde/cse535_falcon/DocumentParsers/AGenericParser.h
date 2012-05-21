/*
 * AGenericParser.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef AGENERICPARSER_H_
#define AGENERICPARSER_H_

#include "../include/includes.h"
#include "../DocumentRepresentation/CDocument.h"

class AGenericParser {

public:
	virtual bool parse_document(CDocument& doc) = 0;
};

#endif /* AGENERICPARSER_H_ */
