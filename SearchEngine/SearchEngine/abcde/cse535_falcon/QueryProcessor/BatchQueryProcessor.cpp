/*
 * BatchQueryProcessor.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: rohit
 */

#include "BatchQueryProcessor.h"
#include "../DocumentParsers/CWhiteSpaceParser.h"
#include "../include/CUtilities.h"
#include "../Indexer/StringHelper.h"
#include "../QueryRepresentation/CQuery.h"
#include "../Ranker/VectorSpaceModel.h"
#include "../Ranker/booleanModel.h"
#include "../Ranker/BM25.h"

BatchQueryProcessor:: BatchQueryProcessor() {

}

BatchQueryProcessor:: ~BatchQueryProcessor() {

}

bool BatchQueryProcessor::process_batch_file(string filename, size_t n) {

	bool status = false;
	int counter = 0;
	vector<string> title;
	vector<string> desc;
	vector<string> narr;
	cout << "Parsing batch file using simple whitespace tokenization" << endl;
	string file_contents = "";
	string line;
	vector<string> qtoken_vec;
	string delim = "\r\n\t ";
    //CBasicTokenProcessor *cbp;
    string temp= "";
    ifstream ifs(filename.c_str());
	if(ifs.is_open()) {
		while(!ifs.eof()) {
			getline(ifs,line);
			file_contents += line;
			file_contents+="\n";
		}
	}
	CUtilities::tokenize(file_contents, qtoken_vec, delim);
	std::vector<string>::iterator qtoken_vec_it;
	qtoken_vec_it = qtoken_vec.begin();

	/** Processing the Document
	 * 1. Populate each Query with
	 * 	- Query ID
	 * 	- Query Desc
	 * 	- Query Narr
	 * 	- Query as a Bag of Words
	 *
	 */

	while(qtoken_vec_it != qtoken_vec.end()) {


		while(*qtoken_vec_it != "</top>") {
			counter ++;
			cout << endl;
			//cout << "Query no:" << counter;
			cout << endl;

			CQuery *query = new CQuery();
			while(*qtoken_vec_it != "Number:"){
				qtoken_vec_it++;
			}
			++qtoken_vec_it;

			// Populate the Query Unique Number
			query->setQueryId(StringHelper::toInt(*qtoken_vec_it));

			// Populate the 'Title' of the Topic/Query
			while(*qtoken_vec_it != "<title>") {
				qtoken_vec_it++;
			}
			++qtoken_vec_it;

			while(*qtoken_vec_it != "<desc>") {
				CUtilities::to_lower(*qtoken_vec_it);
				CBasicTokenProcessor *cbp =new CBasicTokenProcessor();
				temp = cbp->process_token(*qtoken_vec_it);
				if(temp!="") {
					title.push_back(temp);
				//	cout << "title:" << temp << ",";
					}

				qtoken_vec_it++;
			}
			// Set the vector 'Title' to the Topic/Query
			// Also set the title to the final tokens in the Bag of words Query
			query->setQueryTitle(title);
			//query->setQtokens(title);
			cout << endl;

			qtoken_vec_it++;
			qtoken_vec_it++;
			// Populate the Description of Topic/Query
			while(*qtoken_vec_it != "<narr>") {
				CUtilities::to_lower(*qtoken_vec_it);
				CBasicTokenProcessor *cbp =new CBasicTokenProcessor();
				temp = cbp->process_token(*qtoken_vec_it);
					if(temp!="") {
						desc.push_back(temp);
					//	cout << "desc:" << temp << ",";
						}

					qtoken_vec_it++;
			}
			query->setQueryDesc(desc);

			++qtoken_vec_it;
			cout << endl;


			qtoken_vec_it++;
			qtoken_vec_it++;

			while(*qtoken_vec_it != "</top>") {
				CUtilities::to_lower(*qtoken_vec_it);
				CBasicTokenProcessor *cbp =new CBasicTokenProcessor();
				temp = cbp->process_token(*qtoken_vec_it);
				if(temp!="") {
					narr.push_back(temp);
					//cout << "narr:" << temp << ",";
					}

				qtoken_vec_it++;
			}
			// Set the vector 'Narrative' to the Query
			query->setQueryNarr(narr);

			cout << endl;

			/** Add some logic here to include relevant parts of
			 * the narrative into the Bag of Words Query or insert
			 * that logic into your Ranking models
			*/

			++qtoken_vec_it;

			std::vector<std::string>::iterator itr;
             if(CUtilities::zone=="title")
            	 query->setQtokens(title);
             if(CUtilities::zone=="narr")
                 query->setQtokens(narr);
             if(CUtilities::zone=="title+narr")
             {
            	vector<string>::iterator itf;
            	vector<string>temp;
            	for(itf=title.begin();itf!=title.end();itf++)
            	temp.push_back(*itf);
            	for(itf=narr.begin();itf!=narr.end();itf++)
            		temp.push_back(*itf);
            	query->setQtokens(temp);
             }
             if(CUtilities::zone=="title+desc")
                          {
                         	vector<string>::iterator itf;
                         	vector<string>temp;
                         	for(itf=title.begin();itf!=title.end();itf++)
                         	temp.push_back(*itf);
                         	for(itf=desc.begin();itf!=desc.end();itf++)
                         		temp.push_back(*itf);
                         	query->setQtokens(temp);
                          }
             if(CUtilities::zone=="title+narr+desc")
                          {
                         	vector<string>::iterator itf;
                         	vector<string>temp;
                         	for(itf=title.begin();itf!=title.end();itf++)
                         	temp.push_back(*itf);
                         	for(itf=narr.begin();itf!=narr.end();itf++)
                         		temp.push_back(*itf);
                         	for(itf=desc.begin();itf!=desc.end();itf++)
                         	   temp.push_back(*itf);
                         	query->setQtokens(temp);
                          }

			title.clear();
			narr.clear();
			desc.clear();

			//cout << "Just before Calling VSM" << endl;


		//	status = BatchQueryProcessor::processQuery(query);
            if(CUtilities::model=="boolean")
            {
			booleanModel *bm = new booleanModel();
			bm->get_doc_ids(query);
            }

            else if(CUtilities::model == "okapi"){
            				BM25 *okapi = new BM25();
            				okapi->documents_rank(query, n);
            }

          else if(CUtilities::model=="cosine")
            {
            VectorSpaceModel *vsm = new VectorSpaceModel();
			vsm->documents_rank(query,n);
            }


			/** Marks the end of one Query
			 * From here here make calls to your relevant Retrieval
			 * Models - pass the Query obj 'query' as the parameter.
			 */
		}
		++qtoken_vec_it;
	}

	return true;

}
