/*
 * BatchQueryProcessor.h
 *
 *  Created on: Oct 29, 2011
 *      Author: rohit
 */

#ifndef BATCHQUERYPROCESSOR_H_
#define BATCHQUERYPROCESSOR_H_

#include "../QueryRepresentation/CQuery.h"

class BatchQueryProcessor	{
public:
	BatchQueryProcessor();
	~BatchQueryProcessor();

	 bool process_batch_file(string filename, size_t);
};


#endif /* BATCHQUERYPROCESSOR_H_ */
