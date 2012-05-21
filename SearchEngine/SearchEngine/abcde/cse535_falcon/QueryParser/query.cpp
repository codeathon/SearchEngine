/*
 * query.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: nishant
 */

#include "query.h"
#include "../Ranker/VectorSpaceModel.h"

using namespace std;

query::query() {
	// TODO Auto-generated constructor stub

}

query::~query() {
	// TODO Auto-generated destructor stub
}
bool query::prcs_trec_file(string batch_file_path)
{
	bool status = false;
	vector<string> title;
	vector<string> desc;
	vector<string> narr;
	cout << "Parsing batch file using simple whitespace tokenization" << endl;

		string file_contents = "";
		string line;
		vector<string> qtoken_vec;
		string delim = "\r\n\t ";
        CBasicTokenProcessor *cbp;
        string temp= "";

		ifstream ifs(batch_file_path.c_str());
		if(ifs.is_open())
		{
			while(!ifs.eof())
			{
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
										if(temp!="")
										title.push_back(temp);
										qtoken_vec_it++;
									}
									// Set the vector 'Title' to the Topic/Query
									// Also set the title to the final tokens in the Bag of words Query
									query->setQueryTitle(title);
									query->setQtokens(title);


									// Populate the Description of Topic/Query
									while(*qtoken_vec_it != "<narr>") {
										CUtilities::to_lower(*qtoken_vec_it);
										CBasicTokenProcessor *cbp =new CBasicTokenProcessor();
										temp = cbp->process_token(*qtoken_vec_it);
										if(temp!="")
										desc.push_back(temp);
										qtoken_vec_it++;
									}
									++qtoken_vec_it;
                                    query->setQueryDesc(desc);

									while(*qtoken_vec_it != "</top>") {
										CUtilities::to_lower(*qtoken_vec_it);
										CBasicTokenProcessor *cbp =new CBasicTokenProcessor();
										temp = cbp->process_token(*qtoken_vec_it);
										if(temp!="")
										narr.push_back(temp);
										qtoken_vec_it++;
									}
									// Set the vector 'Narrative' to the Query
									query->setQueryNarr(narr);
									/** Add some logic here to include relevant parts of
									 * the narrative into the Bag of Words Query or insert
									 * that logic into your Ranking models
									 */

									qtoken_vec_it++;

									std::vector<std::string>::iterator itr;
									//cout<<"id: "<<query->query_id<<"\n";
									//for(itr = query->query_desc.begin();itr!=query->query_desc.end();++itr)
									//cout<<"narr: "<<*itr<<"\n";


									booleanModel *bm;
									bm->get_doc_ids(query);
									cout<<"\nprocessed";







									title.clear();
									narr.clear();
									desc.clear();

									qtoken_vec_it++;
									/** Marks the end of one Query
									 * From here here make calls to your relevant Retrieval
									 * Models - pass the Query obj 'query' as the parameter.
									 */
								}
								qtoken_vec_it++;

							}

						return true;
					}


