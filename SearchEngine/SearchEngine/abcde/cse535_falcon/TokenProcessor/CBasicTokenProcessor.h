/*
 * CBasicTokenProcessor.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef CBASICTOKENPROCESSOR_H_
#define CBASICTOKENPROCESSOR_H_

#include "../include/includes.h"
#include "../TokenProcessor/ATokenProcessor.h"


class CBasicTokenProcessor : public ATokenProcessor {
public:
	CBasicTokenProcessor();
	virtual ~CBasicTokenProcessor();

	std::string process_token(std::string token);
};

#endif /* CBASICTOKENPROCESSOR_H_ */
