/*
 * forwardIndexer.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: nishant
 */
#include "StringHelper.h"
#include "FileHelper.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/CUtilities.h"
#include "forwardIndexer.h"
using namespace std;
/*************************************
 * Default parameter values.
 * Can be override by constructor
 */
//Counters

//size_t forwardIndexer::_posting_list_size = 0;
//size_t forwardIndexer::_partition_no = 0;

//Boundary
//size_t forwardIndexer::_partition_max_size = 300;
//size_t forwardIndexer::_posting_list_max_size = 30;
size_t forwardIndexer::barrel_id = 0;
vector<size_t>forwardIndexer::doc_ids;
std::multimap<std::size_t,std::string>forwardIndexer::forward_index_map;
string forwardIndexer::_frwd_index_folder = "/home/nishant/op/frwd_index/term_frwd_index";


forwardIndexer::forwardIndexer(string &frwd_indx_folder) {
	// TODO Auto-generated constructor stub
    _frwd_index_folder = frwd_indx_folder;
}

forwardIndexer::~forwardIndexer() {
	// TODO Auto-generated destructor stub
}
bool forwardIndexer::process_directory(string base_directory_path)
{
	bool status = false;

	static int file_num = 0; // for output animation

	string file_resource_path;
	DIR *dirp;
	struct dirent *dp;
	//struct stat buf;

	dirp = opendir(base_directory_path.c_str());
	if (!dirp) {
		cout << "Dirp is null" << endl;
		return false;
	}
	std::string file_resource_name;
	while ((dp = readdir(dirp))) {
		file_resource_name = dp->d_name;

		file_resource_path = base_directory_path + '/' + file_resource_name;

		if ((file_resource_name == ".") || (file_resource_name == "..")
				|| (file_resource_name == "CVS"))
			continue;


				++file_num;
				process_file(file_resource_path);
          	  if(forward_index_map.size()>=10000)
          	  {
          		  string index_st;
          		  //ofstream ofs;
          		  std::vector<size_t>::iterator vec_itr;
          		  char temp[100];
          		  std::map<size_t,std::string>::iterator index_it;
          		  ofstream frwd_fs;
          		  //ofs<<barrel_id;
          		  index_st = _frwd_index_folder+"frwd.indx.";
          		  sprintf (temp, "%03d", barrel_id);
          		  index_st.append(temp);

          		  frwd_fs.open(index_st.c_str(),ios::app);

          		  for(vec_itr= doc_ids.begin();vec_itr != doc_ids.end();++vec_itr)
          		  {
          			  frwd_fs<<"DocId:"<<*vec_itr<<"\n";
          			  index_it = forwardIndexer::forward_index_map.find(*vec_itr);

          			  while(index_it!=forwardIndexer::forward_index_map.end() && (*index_it).first==(*vec_itr))
          			  {
          				  frwd_fs<<(*index_it).second<<"\n";
          				  index_it++;
          			  }

          		  }
          		    forward_index_map.clear();
          		    ++barrel_id;
          		    doc_ids.clear();
          		    frwd_fs.close();

          	  }


	}
	closedir(dirp);
		status = true;

		return status;

}
	bool forwardIndexer::process_file(std::string filename)
	{
		//cout<<"The file picked up for forward indexing is:"<<filename<<endl;
     		string file_contents = "";
			string line;
			vector<string> token_vec;
			string delim = "\r\n\t ";
			std::string section = "";
            bool status;
            int t=0;
            string index_st;
            ofstream index_fs;
			ifstream ifs(filename.c_str());
			if ( ifs.is_open() ) {

				while ( !ifs.eof() ) {
					getline( ifs, line );
					if(t==1)
					{
						size_t temp_int = StringHelper::toInt(line);
                     file_id = temp_int;
					doc_ids.push_back(StringHelper::toInt(line));
					}
					t++;
					file_contents += line;
					file_contents+='\n';
				}

				CUtilities::tokenize(file_contents, token_vec, delim);
				vector<std::string>::iterator raw_token_it;
                 std::multimap<size_t,std::string> temp_mm;
				CBasicTokenProcessor* cbtp = new CBasicTokenProcessor();
					for(raw_token_it = token_vec.begin();raw_token_it!=token_vec.end();++raw_token_it)
				{
			//		cout<<"Raw Token:"<<*raw_token_it<<endl;
                  if((*raw_token_it)=="<<#WikiFileId>>")
                	  section = "WikiFileId";
                  if((*raw_token_it)=="<<#Article")
                	  section = "ArticleTitle";
                  if((*raw_token_it)=="<<#Timestamp>>")
                	  section = "Timestamp";
                  if((*raw_token_it)=="<<#Infobox>>")
                	  section = "Infobox";
                  if((*raw_token_it)=="<<#Sections>>")
                	  section = "Section";
                  if((*raw_token_it)=="<<#LINKS>>")
                	  section = "Links";
                  if((*raw_token_it)=="<<#Categories>>")
                	  section = "Category";
                  if((*raw_token_it)=="<<#Author>>")
                	  section = "Author";


                   if(CDocument::_raw_normal_map.find(*raw_token_it)!=CDocument::_raw_normal_map.end())
                   {
                	   stringstream ofs;
                	 //  cout<<"Inside if:"<<*raw_token_it<<endl;
                	   string nrml=CDocument::_raw_normal_map[*raw_token_it];
                	//   cout<<"Normal"<<nrml<<endl;
                	   //cout

                	  int temp = CDocument::term_dict[nrml];
//                	  temp_mm.insert(pair<size_t,std::string>(temp,section));
                	 ofs<<temp;


                	  string id_loc = ofs.str()+","+section;

                	  forward_index_map.insert(pair<std::size_t,std::string>(file_id,id_loc));
                	 // cout<<"File inside: "<<indexer::forward_index_map.size();

//                	  cout<<"FileInside: "<<indexer::forward_index_map.size()<<endl;
                   }

				}


				token_vec.clear();
			} else {
				cout << "Couldn't open file " << filename << endl;
			}

			ifs.close();
			status = true;

			return status;
		}
