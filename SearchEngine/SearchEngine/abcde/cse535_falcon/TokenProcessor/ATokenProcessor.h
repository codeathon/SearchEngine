/*
 * ATokenProcessor.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef ATOKENPROCESSOR_H_
#define ATOKENPROCESSOR_H_

#include "../include/includes.h"

class ATokenProcessor {

public:
	virtual std::string process_token(std::string token) = 0;
};

#endif /* ATOKENPROCESSOR_H_ */
