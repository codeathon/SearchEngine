/*
 * CWikiTokenProcessor.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef CWIKITOKENPROCESSOR_H_
#define CWIKITOKENPROCESSOR_H_

#include "../include/includes.h"
#include "CBasicTokenProcessor.h"

class CWikiTokenProcessor : public CBasicTokenProcessor {
static CWikiTokenProcessor* _wiki_token_processor;
public:
	CWikiTokenProcessor();
	virtual ~CWikiTokenProcessor();
	inline static CBasicTokenProcessor* get_instance()
	{
		if(_wiki_token_processor==0)
			_wiki_token_processor = new CWikiTokenProcessor();

		 return _wiki_token_processor;

	}

	std::string process_token(std::string token);
};

#endif /* CWIKITOKENPROCESSOR_H_ */
