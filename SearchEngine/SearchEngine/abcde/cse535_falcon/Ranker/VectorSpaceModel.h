/*
 * VectorSpaceModel.h
 *
 *  Created on: Oct 29, 2011
 *      Author: rohit
 */

#ifndef VECTORSPACEMODEL_H_
#define VECTORSPACEMODEL_H_

#include "../QueryRepresentation/CQuery.h"

using namespace std;

class VectorSpaceModel	{
public:
	VectorSpaceModel();
	~VectorSpaceModel();
	static 	map<string,double> score;
	bool documents_rank(CQuery *query, size_t n);
};


#endif /* VECTORSPACEMODEL_H_ */
