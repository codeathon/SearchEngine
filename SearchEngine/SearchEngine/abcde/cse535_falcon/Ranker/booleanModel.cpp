/*
 * booleanModel.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: nishant
 */

#include "booleanModel.h"
#include "../Indexer/Config.h"
#include "../DocumentRepresentation/CDocument.h"
#include "../DocumentProcessor/CDocumentProcessor.h"
#include "../QueryRepresentation/CQuery.h"
#include "../include/CUtilities.h"
#include <math.h>
#include <algorithm>
#include <iomanip>
using namespace std;

booleanModel::booleanModel() {
	// TODO Auto-generated constructor stub
final_docs.clear();

}

booleanModel::~booleanModel() {
	// TODO Auto-generated destructor stub
}

bool booleanModel::get_doc_ids(CQuery *query)
{
	vector<string>::iterator query_it;
	vector<size_t>::iterator doc_id;
	string qout = Config::getValue("query_out");
	qout = qout +"/Query_Output.txt";
	ofstream ofs;
	ofs.open(qout.c_str(),fstream::app);
    multimap<double, string> score_sort;
	for (query_it = query->qtokens.begin(); query_it != query->qtokens.end(); query_it++)
		{
			vector<std::string>temp;
			//cout<<"token:"<<*query_it<<"\n";
			map<string, int>::iterator doc_freq_it;
			map<string,int> doc_freq;
			string doc_name;
			if(CDocument::term_cnt_dict.find(*query_it) != CDocument::term_cnt_dict.end())
			{
			doc_freq = CDocument::term_cnt_dict[*query_it];
			for(doc_freq_it = doc_freq.begin(); doc_freq_it != doc_freq.end(); doc_freq_it++)
			{
			doc_name = (*doc_freq_it).first;
			temp.push_back(doc_name);
			}

 	       }
			if(final_docs.size()==0)
			final_docs = temp;
			else
			{

				{
		                  vector<string>temp2;
		                  std::vector<std::string>::iterator it1;
		                  std::vector<std::string>::iterator it2;
		                  temp2 = final_docs;
		                  final_docs.clear();
		                  int x,y;
		                  x = temp2.size();
		                  y=temp.size();
		                  if(x<y)
		                  {
		                	  for(it1=temp2.begin();it1!=temp2.end();++it1)
		                		  for(it2=temp.begin();it2!=temp.end();++it2)
		                		  {
		                			  if(*it1==*it2)
		                				  final_docs.push_back(*it1);
		                		  }
		                  }
		                  else
		                  {
		                	  for(it1=temp.begin();it1!=temp.end();++it1)
		                 		  for(it2=temp2.begin();it2!=temp2.end();++it2)
		                  		  {
		               			  if(*it1==*it2)
		         				  final_docs.push_back(*it1);
		                 		  }
		                  }



			}
		}
		}
	vector<string>::iterator its;
	int counter = 0;
	if(CUtilities::online_mode_enabled==1)
	{
		if(CUtilities::num_for_onlie_mode>final_docs.size())
			CUtilities::num_for_onlie_mode = final_docs.size();
		cout<<"The number of documents retrieved = "<<CUtilities::num_for_onlie_mode<<endl;
	}
		for(its=final_docs.begin();its!=final_docs.end();++its)
		{
			int w=0;
			string file_contents,line;
			counter++;
			string str;
			str = *its;
			size_t last_pos = str.rfind('\/');
			str = str.substr(last_pos, string::npos);
			CUtilities::delete_character(str, '\/');
			if(CUtilities::online_mode_enabled==1)
			{
				if(counter>CUtilities::num_for_onlie_mode)
				return true;
				string fname;

				int docID = CDocument::doc_name_doc_id[*its];
				//cout<<"id :"<<docID<<endl;
				stringstream ss;
				ss<<docID;

				if((*its).find("wiki")!=string::npos)
				{
					fname= CUtilities::semwiki_dir_path +"/" + ss.str() +"_semwiki.txt";
					w=1;
				}
				else
				{
					fname = *its;
				}

				ifstream ifs(fname.c_str());
				int c=0;
				while ( !ifs.eof() ) {
					        c++;
					        if(c>=11&&w==0)
					        	break;
					        getline( ifs, line );
							file_contents += line;
							file_contents+='\n';
						}
				cout<<"Document :"<<*its<<endl;
				cout<<"Contents:"<<file_contents<<endl;
			}
			else
			ofs<<query->getQueryId() << "\t" << "0" << "\t" << str << "\t" << final_docs.size() << "\t" << "0" << "\t" << "backrub" << "\n";
		}

		return true;

}


