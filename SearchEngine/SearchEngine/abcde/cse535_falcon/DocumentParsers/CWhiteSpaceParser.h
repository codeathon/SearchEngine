/*
 * CWhiteSpaceParser.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef CWHITESPACEPARSER_H_
#define CWHITESPACEPARSER_H_

#include "../include/includes.h"
#include "../include/CUtilities.h"
#include "CBaseParser.h"

class CWhiteSpaceParser : public CBaseParser {

	static CWhiteSpaceParser* _white_space_parser;
	CWhiteSpaceParser();

public:

	/**
	 * @brief static
	 */
	inline static CBaseParser* get_instance() {
		if ( _white_space_parser == 0 )
			_white_space_parser = new CWhiteSpaceParser();

		return _white_space_parser;
	}

	virtual ~CWhiteSpaceParser();

	bool parse_document(CDocument& doc);
};

#endif /* CWHITESPACEPARSER_H_ */
