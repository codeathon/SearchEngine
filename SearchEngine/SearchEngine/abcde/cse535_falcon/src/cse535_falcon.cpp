//============================================================================
// Name        : Falcon.cpp
// Author      : Eric (Li, Xiaoyi)
// Version     :
// Copyright   : Your copyright notice

//============================================================================

#include "../include/includes.h"
#include "../DocumentProcessor/CDocumentProcessor.h"
#include "../DocumentParsers/CWikiMarkupParser.h"
#include "../DocumentRepresentation/CDocument.h"
#include "../include/CUtilities.h"
#include "../Indexer/Config.h"
#include "../Indexer/InvertedIndexer.h"
#include "../Indexer/forwardIndexer.h"
#include "../QueryParser/query.h"
#include "../QueryProcessor/BatchQueryProcessor.h"
#include "../QueryProcessor/OnlineQueryProcessor.h"
#include "../QueryRepresentation/CQuery.h"
#include "../TokenProcessor/CBasicTokenProcessor.h"
#include<time.h>

using namespace std;

int main(int argc, char** argv) {
	if ( argc < 3 ) {
		cout << "Usage: " << argv[0] << "-i <ConfigureFilePath>" << endl;
		exit(1);
	}

	string indexMode = argv[1];
	if(indexMode =="-i")
	{
	cout<< "==============================================================" << endl;
	cout << "                 Running in index mode." << endl;
	cout<< "==============================================================" << endl;
	}

	else if(indexMode =="-r")
	       {
	    		cout<< "==============================================================" << endl;
	    		cout << "                 Running in batch mode." << endl;
	    		cout<< "==============================================================" << endl;
	       }
	else if(indexMode=="-s")
	{
		cout<< "==============================================================" << endl;
		cout << "                 Running in batch mode." << endl;
		cout<< "==============================================================" << endl;
		CUtilities::online_mode_enabled = 1;

	}
	else
	{
		cout<<"Wrong mode selected"<<endl;
		exit(1);
	}
	string configDir = argv[2];
	Config *cfg = new Config(configDir);

	string base_dir = cfg->getValue("data_dir");
	string dict_dir = cfg->getValue("dict_dir");
	string semwiki_dir = cfg->getValue("semwiki_dir");
	string qbatch_file  = cfg->getValue("query_batch_file");
	CUtilities::zone =cfg->getValue("zone");
//     cout<<"Base dir:"<<base_dir<<endl;
  //   cout<<"dict dir:"<<dict_dir<<endl;
    // cout<<"semwiki_dir:"<<semwiki_dir<<endl;
     CUtilities::dir_path = dict_dir;
     CUtilities::semwiki_dir_path = semwiki_dir;
	//DIR *pdir;

	CDocumentProcessor dp;
	dp.count_files_to_process(base_dir);
	cout << dp.get_num_files_to_process() << " files to process" << endl;

    CUtilities::make_directory(dict_dir);
    CUtilities::make_directory(semwiki_dir);

    string frwdIndexFolder = Config::getValue("frwd_indx_folder");
    CUtilities::make_directory(frwdIndexFolder);
    forwardIndexer *frwdIndexer = new forwardIndexer(frwdIndexFolder);

	string invIndexFolder = Config::getValue("term_inv_index_folder");
	CUtilities::term_indx_dirx_path = invIndexFolder;
	size_t partitionMaxSize = StringHelper::toInt(Config::getValue("partition_max_size"));
	size_t postingListMaxSize = StringHelper::toInt(Config::getValue("posting_list_max_size"));
	CUtilities::make_directory(invIndexFolder);
	InvertedIndexer *indexer = new InvertedIndexer(invIndexFolder, partitionMaxSize, postingListMaxSize);

    std::string cat_st,author_st,link_st,rawtok_st,termdict_st,termcnt_st,norm_raw_st,file_st;
    cat_st = dict_dir + "/Categories.txt";
    author_st = dict_dir + "/authors.txt";
    rawtok_st = dict_dir + "/raw_tokenDict.txt";
    termdict_st = dict_dir + "/TermDictionary.txt";
    termcnt_st = dict_dir + "/TermCountDictionary.txt";
    norm_raw_st = dict_dir + "/RawNormal.txt";
    link_st = dict_dir + "/linkRepository.txt";
    file_st = dict_dir + "/FileDictionary.txt";


	 dp.process_directory(base_dir);
     ofstream cat_fs,author_fs,link_fs,raw_tok_fs,term_dict_fs,term_cnt_dict_fs,raw_normal_map_fs,file_ofs,frwd_fs;
     cat_fs.open(cat_st.c_str(),ios::trunc);
     author_fs.open(author_st.c_str(),ios::trunc);
     link_fs.open(link_st.c_str(),ios::trunc);
     raw_tok_fs.open(rawtok_st.c_str(),ios::trunc);
     term_dict_fs.open(termdict_st.c_str(),ios::trunc);
     term_cnt_dict_fs.open(termcnt_st.c_str(),ios::trunc);
     raw_normal_map_fs.open(norm_raw_st.c_str(),ios::trunc);
     file_ofs.open(file_st.c_str(),ios::app);
     std::map<std::string,int>::iterator cat_it;
     std::multimap<std::string,std::string>::iterator link_it,raw_normal_map_itr;
     std::map<std::string,int>::iterator author_it;
     std::map<std::string,size_t>::iterator raw_tok_itr;
     std::map<std::string,size_t>::iterator term_dict_itr;
     std::map<size_t,int>::iterator term_cnt_dict_itr;
     std::map<size_t,size_t>::iterator file_it;
     std::multimap<size_t,std::string>::iterator index_it;
     std::vector<size_t>::iterator vec_itr;


     for(file_it =CDocumentProcessor::file_dict.begin(); file_it!=CDocumentProcessor::file_dict.end(); ++file_it)
     {
     file_ofs << (*file_it).first << "," << CDocumentProcessor::_barrel_id << "," << (*file_it).second <<"$ ";
     }

     for(cat_it=CWikiMarkupParser::_category_map.begin();cat_it!=CWikiMarkupParser::_category_map.end();++cat_it)
     {
         cat_fs<<(*cat_it).first<<" "<<(*cat_it).second<<"\n";
     }
     for(author_it=CWikiMarkupParser::_author_map.begin();author_it!=CWikiMarkupParser::_author_map.end();++author_it)
          {
              author_fs<<(*author_it).first<<" "<<(*author_it).second<<"\n";
          }
     for(link_it=CWikiMarkupParser::_link_set_map.begin();link_it!=CWikiMarkupParser::_link_set_map.end();++link_it)
          {
              link_fs<<(*link_it).first<<" "<<(*link_it).second<<"\n";
          }
     for(raw_tok_itr = CDocument::_raw_token_id_map.begin();raw_tok_itr!=CDocument::_raw_token_id_map.end();++raw_tok_itr)
     {
    	 raw_tok_fs<<(*raw_tok_itr).first<<"  "<<(*raw_tok_itr).second<<"\n";
     }
     for(raw_normal_map_itr = CDocument::_raw_normal_map.begin();raw_normal_map_itr!=CDocument::_raw_normal_map.end();++raw_normal_map_itr)
     {
    	 raw_normal_map_fs<<(*raw_normal_map_itr).first<<"  "<<(*raw_normal_map_itr).second<<" $ ";
     }
     for(term_dict_itr = CDocument::term_dict.begin();term_dict_itr!=CDocument::term_dict.end();++term_dict_itr)
     {
    	 term_dict_fs<<(*term_dict_itr).first<<"  "<<(*term_dict_itr).second<<" $ "<<"\n";
     }
     /*
     for(term_cnt_dict_itr = CDocument::term_cnt_dict.begin();term_cnt_dict_itr!=CDocument::term_cnt_dict.end();++term_cnt_dict_itr)
     {
    	 term_cnt_dict_fs<<(*term_cnt_dict_itr).first<<"  "<<(*term_cnt_dict_itr).second<<" $ ";
     }
     */
    // CDocument::term_cnt_dict.clear();
     CDocument::term_dict.begin();
     CDocument::_raw_normal_map.clear();
     CDocument::_raw_token_id_map.clear();
     CWikiMarkupParser::_link_set_map.clear();
     CWikiMarkupParser::_author_map.clear();
     CWikiMarkupParser::_category_map.clear();
     CDocumentProcessor::file_dict.clear();
     cat_fs.close();
     author_fs.close();
     link_fs.close();
     raw_tok_fs.close();
     term_dict_fs.close();
     term_cnt_dict_fs.close();
     raw_normal_map_fs.close();
     file_ofs.close();

     char temp[100];
     std::string index_st;
     index_st =frwdIndexFolder +"frwd.indx.";
     sprintf (temp, "%03d",forwardIndexer::barrel_id);
     index_st.append(temp);

     frwd_fs.open(index_st.c_str(),ios::app);

     for(vec_itr=forwardIndexer::doc_ids.begin();vec_itr != forwardIndexer::doc_ids.end();++vec_itr)
     {
               			  frwd_fs<<"DocId:"<<*vec_itr<<"\n";
               			  index_it = forwardIndexer::forward_index_map.find(*vec_itr);

               			  while(index_it!=forwardIndexer::forward_index_map.end() && (*index_it).first==(*vec_itr))
               			  {
               				  frwd_fs<<(*index_it).second<<"\n";
               				  index_it++;
               			  }

               		  }
               		forwardIndexer::forward_index_map.clear();
               		++(forwardIndexer::barrel_id);
               		forwardIndexer::doc_ids.clear();
               		frwd_fs.close();
        string model = cfg->getValue("query_model");
        CUtilities::model = model;
       if(indexMode =="-r")
       {
    	BatchQueryProcessor *bqp = new BatchQueryProcessor();
	    bqp->process_batch_file(qbatch_file,dp.get_num_files_to_process());
       }

       if(indexMode =="-s")
       {
    	   std::string delim = "\r\n\t ";
    	   std::string user_query;
    	   do
    	   {

    	       cout<<"Enter your query:"<<endl;
    		   cout<<"The query should of the form [number] query"<<endl;
    		   getline(cin,user_query);
    		   if(user_query=="@exit")
                  break;
    		   OnlineQueryProcessor *op = new OnlineQueryProcessor();
    		   op->processQuery(user_query,model,dp.get_num_files_to_process());

    	   }while(user_query!="@exit");
       }



	return 0;
}
