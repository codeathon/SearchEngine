/*
 * VectorSpaceModel.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: rohit
 */

#include "VectorSpaceModel.h"
#include "../DocumentRepresentation/CDocument.h"
#include "../DocumentProcessor/CDocumentProcessor.h"
#include "../QueryRepresentation/CQuery.h"
#include "../include/CUtilities.h"
#include <math.h>
#include <algorithm>
#include "../Indexer/Config.h"

using namespace std;

VectorSpaceModel:: VectorSpaceModel() {

}

VectorSpaceModel:: ~VectorSpaceModel() {

}

std::map<string, double> VectorSpaceModel::score;

bool VectorSpaceModel::documents_rank(CQuery *query, size_t n) {

    vector<string>::iterator query_it;
    vector<size_t>::iterator doc_id;
    string qout = Config::getValue("query_out");
    qout = qout +"/Query_Output.txt";
    ofstream ofs;
    ofs.open(qout.c_str(),fstream::app);

    double score_vsm =0.0;
    bool status;
    multimap<double, string> score_sort;
    int counter = 0;

    for (query_it = query->qtokens.begin(); query_it != query->qtokens.end(); query_it++) {

        // Term Frequency
        size_t tf;

        // Document Frequency = size(posting_list)
        double df;

        // Inverse Document Frequency
        double idf;

           //docName, freq
        map<string, int>::iterator doc_freq_it;

        // sub map
        map<string,int> doc_freq;

        double score_temp;

        string doc_name;

        if(CDocument::term_cnt_dict.find(*query_it) != CDocument::term_cnt_dict.end()) {
            doc_freq = CDocument::term_cnt_dict[*query_it];
            df = (double)doc_freq.size();
            idf = (double)log(n/df);

            for(doc_freq_it = doc_freq.begin(); doc_freq_it != doc_freq.end(); doc_freq_it++) {
                doc_name = (*doc_freq_it).first;
                tf = (double)(*doc_freq_it).second;
                score_vsm = tf*idf;
                score_temp = VectorSpaceModel::score[doc_name];
                score_temp+=score_vsm;
                VectorSpaceModel::score[doc_name] = score_temp;
                score_sort.insert(pair<double, string>(score_temp,doc_name));
            }
        }
    }
//    std::sort(VectorSpaceModel::score.begin(),VectorSpaceModel::score.end());
    int c=0;
    	if(CUtilities::online_mode_enabled==1)
    		{
    			if(CUtilities::num_for_onlie_mode>score_sort.size())
    			CUtilities::num_for_onlie_mode = score_sort.size();
    			cout<<"The number of documents retrieved = "<<CUtilities::num_for_onlie_mode<<endl;
    		}
    multimap<double,string>::reverse_iterator score_it;

    for(score_it = score_sort.rbegin(); score_it!= score_sort.rend(); score_it++) {
        counter++;
        c++;
        int w=0;
        string file_contents,line;
        string str,str2;
        str2 = (*score_it).second;
        str = (*score_it).second;
        size_t last_pos = str.rfind('\/');
        str = str.substr(last_pos, string::npos);
        CUtilities::delete_character(str, '\/');

        if(CUtilities::online_mode_enabled==1)
        					{
        						if(c>CUtilities::num_for_onlie_mode)
        						return true;
        						string fname;

        						int docID = CDocument::doc_name_doc_id[str2];
        						//cout<<"id :"<<docID<<endl;
        						stringstream ss;
        						ss<<docID;

        						if(str2.find("wiki")!=string::npos)
        						{
        							fname= CUtilities::semwiki_dir_path +"/" + ss.str() +"_semwiki.txt";
        							w=1;
        						}
        						else
        						{
        							fname = str2;
        						}

        						ifstream ifs(fname.c_str());
        						int k=0;
        						while ( !ifs.eof() ) {
        							        k++;
        							        if(k>=11&&w==0)
        							        	break;
        							        getline( ifs, line );
        									file_contents += line;
        									file_contents+='\n';
        								}
        						cout<<"Document :"<<str2<<endl;
        						cout<<"Contents:"<<file_contents<<endl;
        					}
        else

        ofs<<query->getQueryId() << "\t" << "0" << "\t" << str << "\t" << counter << "\t" << setprecision(5) << (*score_it).first << "\t" << "backrub" << "\n";
    }

    VectorSpaceModel::score.clear();
    score_sort.clear();
    status = true;
    return status;
}
