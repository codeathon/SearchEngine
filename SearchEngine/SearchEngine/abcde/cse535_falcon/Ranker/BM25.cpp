/*
 * BM25.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: Jun Wu
 */

#include "BM25.h"

BM25::BM25() {
	// TODO Auto-generated constructor stub

}

BM25::~BM25() {
	// TODO Auto-generated destructor stub
}

map<string, float> BM25::doc_score_map;
int BM25::top_k = 30;
bool BM25::documents_rank(CQuery *query, size_t n){
	priority_queue<QueryResult> ranking_result;
	vector<string>::iterator query_itr;
	for (query_itr = query->qtokens.begin(); query_itr != query->qtokens.end(); query_itr++) {

		float score;
		int df;
		int idf;
		int tf;
		int ave_length;
		int doc_length;
		float k1 = 1.2;
		float b = 0.75;

		map<string,int> doc_freq;

		if(CDocument::term_cnt_dict.find(*query_itr) != CDocument::term_cnt_dict.end()) {
			doc_freq = CDocument::term_cnt_dict[*query_itr];
			df = (float)doc_freq.size();
			idf = (float)log10(n/df);
			ave_length = 1000;
			doc_length = 1000;

			map<string, int>::iterator doc_freq_itr;
			for(doc_freq_itr = doc_freq.begin(); doc_freq_itr != doc_freq.end(); doc_freq_itr++) {
				string doc_name = (*doc_freq_itr).first;
				tf = (double)(*doc_freq_itr).second;
				score = idf * ( (k1+1)*tf )/( k1*( (1-b) + b*(doc_length/ave_length) ) + tf );
				doc_score_map[doc_name] += score;
			}
		}
	}

	string query_output_dir = Config::getValue("query_out");
	CUtilities::make_directory(query_output_dir);
	string query_output_path = query_output_dir + "/Query_Output.txt";
	ofstream query_out_stream(query_output_path.c_str(), fstream::app);

	map<string, float>::iterator score_itr;
	for(score_itr = doc_score_map.begin(); score_itr != doc_score_map.end(); score_itr++) {
		QueryResult *result = new QueryResult(query->getQueryId(), score_itr->first, 0, score_itr->second);
		ranking_result.push(*result);
	}

	if(CUtilities::online_mode_enabled==1)
		{
			if(CUtilities::num_for_onlie_mode > ranking_result.size())
				CUtilities::num_for_onlie_mode = ranking_result.size();
			cout<<"The number of documents retrieved = "<<CUtilities::num_for_onlie_mode<<endl;
		}
	int counter=0;

	for(int i = 1; i <= ranking_result.size(); i++){

		//if(i > top_k)
			//break;
		int w=0;
	    string file_contents,line;
		counter++;

		QueryResult out_result = ranking_result.top();
		ranking_result.pop();

		if(out_result.score == 0)
			break;

		string short_file_name = out_result.documentName.substr(out_result.documentName.rfind('\/'));
		CUtilities::delete_character(short_file_name, '\/');

		if(CUtilities::online_mode_enabled==1)
					{
						if(counter>CUtilities::num_for_onlie_mode)
						return true;
						string fname;

						int docID = CDocument::doc_name_doc_id[out_result.documentName];
						//cout<<"id :"<<docID<<endl;
						stringstream ss;
						ss<<docID;

						if(out_result.documentName.find("wiki")!=string::npos)
						{
							fname= CUtilities::semwiki_dir_path +"/" + ss.str() +"_semwiki.txt";
							w=1;
						}
						else
						{
							fname = out_result.documentName;
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
						cout<<"Document :"<<out_result.documentName<<endl;
						cout<<"Contents:"<<file_contents<<endl;
					}
					else
		query_out_stream << out_result.topic << "\t" << "0" << "\t" << short_file_name << "\t" << i << "\t" << setprecision(5) << out_result.score << "\t" << "backrub" << "\n";
	}

	doc_score_map.clear();
	return true;
}
