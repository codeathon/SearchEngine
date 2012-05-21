/*
 * OnlineQueryProcessor.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: rohit
 */


#include "OnlineQueryProcessor.h"
#include "../include/CUtilities.h"

OnlineQueryProcessor:: OnlineQueryProcessor() {

}

OnlineQueryProcessor::~OnlineQueryProcessor() {

}

bool OnlineQueryProcessor::processQuery(string user_query,string model,int n) {
time_t tbegin;
time(&tbegin);
tbegin = time(NULL);

string delim = "\n\r\t ";
int space_pos = user_query.find(" ");
vector<string>tok_vec;
vector<string>::iterator itr;
CQuery *cq = new CQuery();
CBasicTokenProcessor *cbp = new CBasicTokenProcessor();

string a = user_query.substr(0,space_pos);
CUtilities::delete_character(a,'[');
CUtilities::delete_character(a,']');

CUtilities::num_for_onlie_mode = CUtilities::toInt(a);
string b = user_query.substr(space_pos+1);
CUtilities::tokenize(b,tok_vec,delim);

for(itr=tok_vec.begin();itr!=tok_vec.end();++itr)
{
	cq->qtokens.push_back(cbp->process_token(*itr));
}
	if(model=="boolean")
	{
		booleanModel *bm = new booleanModel();
		bm->get_doc_ids(cq);
	}
	else if(model=="cosine")
	{
		VectorSpaceModel *vsm = new VectorSpaceModel();
		vsm->documents_rank(cq,n);
	}

	else if(CUtilities::model == "okapi"){
	            				BM25 *okapi = new BM25();
	            				okapi->documents_rank(cq, n);
	            }

	time_t tfinish;
    time(&tfinish);
	tfinish = time(NULL);
	cout << "Total time to process = " << (tfinish - tbegin) / 60.0 << " mins"<<endl;
}
