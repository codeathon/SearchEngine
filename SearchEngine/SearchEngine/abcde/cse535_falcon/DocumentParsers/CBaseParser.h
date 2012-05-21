/*
 * CBaseParser.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef CBASEPARSER_H_
#define CBASEPARSER_H_

#include "../include/includes.h"
#include "AGenericParser.h"

class CBaseParser: public AGenericParser {

public:
	CBaseParser();

	/**
	 * @brief static
	 */
	inline static CBaseParser* get_instance() {
		return 0;
	}

	virtual ~CBaseParser();

	virtual bool parse_document(CDocument& doc);
};

#endif /* CBASEPARSER_H_ */
