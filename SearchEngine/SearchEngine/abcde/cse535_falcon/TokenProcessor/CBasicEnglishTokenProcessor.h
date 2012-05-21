/*
 * CBasicEnglishTokenProcessor.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef CBASICENGLISHTOKENPROCESSOR_H_
#define CBASICENGLISHTOKENPROCESSOR_H_

#include "../include/includes.h"
#include "CBasicTokenProcessor.h"
#include "../include/CUtilities.h"
#include "CBasicEnglishTokenProcessor.h"

class CBasicEnglishTokenProcessor : public CBasicTokenProcessor {

public:
	CBasicEnglishTokenProcessor();
	virtual ~CBasicEnglishTokenProcessor();

	std::string process_token(std::string token);
};

#endif /* CBASICENGLISHTOKENPROCESSOR_H_ */
