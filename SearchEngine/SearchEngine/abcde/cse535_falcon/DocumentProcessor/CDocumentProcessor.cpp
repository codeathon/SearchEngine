/*
 * CDocumentProcessor.cpp
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#include "CDocumentProcessor.h"
#include "../include/CUtilities.h"
#include "../DocumentRepresentation/CDocument.h"
#include "../DocumentParsers/CBaseParser.h"
#include "../DocumentParsers/CWhiteSpaceParser.h"
#include "../DocumentParsers/CWikiMarkupParser.h"
#include "../Indexer/InvertedIndexer.h"
#include "../Indexer/Config.h"
#include "../Indexer/forwardIndexer.h"

using namespace std;
std::map<size_t,size_t> CDocumentProcessor::file_dict;
size_t CDocumentProcessor:: _barrel_id;

CDocumentProcessor::CDocumentProcessor() {
	_num_total_files_to_process = 0;
	_global_file_id = 0;
	// setting up document features map
	_doc_major_category_map["other"] = 0;
	_doc_major_category_map["news"] = 1;
	_doc_major_category_map["wiki"] = 2;
	// setting up document parsers map
	_doc_parser_map["other"] = CWhiteSpaceParser::get_instance();
	_doc_parser_map["news"] = CWhiteSpaceParser::get_instance();
	_doc_parser_map["wiki"] = CWikiMarkupParser::get_instance();
}

CDocumentProcessor::~CDocumentProcessor() {

}

/**
 * @brief
 * @param base_directory_string
 * @return
 */
bool CDocumentProcessor::count_files_to_process(
		std::string base_directory_path) {
	bool status = false;

	string file_resource_path;
	DIR *dirp;
	struct dirent *dp;
	struct stat buf;

	dirp = opendir(base_directory_path.c_str());
	if (!dirp) {
		cout << "Dirp is null" << endl;
		return false;
	}
	string file_resource_name;
	while ((dp = readdir(dirp))) {
		file_resource_name = dp->d_name;

		file_resource_path = base_directory_path + '/' + file_resource_name;
		//cout << "dp->d_name = " << file_resource_name << endl;

		if ((file_resource_name == ".") || (file_resource_name == "..")
				|| (file_resource_name == "CVS"))
			continue;

		if (stat(file_resource_path.c_str(), &buf) == 0) {
			// recursively process directories
			if (buf.st_mode & S_IFDIR
				)
				count_files_to_process(file_resource_path);
			else
				++_num_total_files_to_process;
		}
	}
	closedir(dirp);
	status = true;

	return status;
}

/**
 * @brief
 * @param directory_string
 * @return
 */
bool CDocumentProcessor::process_directory(string directory_path) {

	cout
			<< "\nPlease wait while the system creates the dictionaries from the corpus.."
			<< endl;
	cout
			<< "Depending on the size and number of the files to be processed, it may take several minutes.."
			<< endl;
	cout << "\nSystem busy ..." << endl;

	time_t tbegin;
	time(&tbegin);
	//cout << "Time now is : " << ctime(&tbegin) << endl;
	tbegin = time(NULL);

	// --------------------------------------------

	bool status = process_directory_recursively(directory_path);

	cout<<"Starting the forward indexing process"<<endl;
	string frwdIndexFolder = Config::getValue("frwd_indx_folder");
	 forwardIndexer *fi = new forwardIndexer(frwdIndexFolder);
	 fi->process_directory(CUtilities::semwiki_dir_path);


	// --------------- some more couts ---------------
	time_t tfinish;
	time(&tfinish);
	//cout << "\nTime now is : " << ctime(&tfinish) << endl;
	tfinish = time(NULL);
	//cout << "Total time to process = " << (tfinish - tbegin) / 60.0 << " mins"
			//<< endl;
	//cout << "Done with processing.. and about to exit the program." << endl;
	return status;
}

/**
 * @brief
 * @param base_dir_path
 * @param cur_dir_name
 * @param total_files
 * @return
 */
bool CDocumentProcessor::process_directory_recursively(
		string base_directory_path, string partial_directory_name) {
	bool status = false;

	static int file_num = 0; // for output animation

	string file_resource_path;
	DIR *dirp;
	struct dirent *dp;
	struct stat buf;

	dirp = opendir(base_directory_path.c_str());
	if (!dirp) {
		cout << "Dirp is null" << endl;
		return false;
	}
	string file_resource_name;
	while ((dp = readdir(dirp))) {
		file_resource_name = dp->d_name;

		file_resource_path = base_directory_path + '/' + file_resource_name;

		if ((file_resource_name == ".") || (file_resource_name == "..")
				|| (file_resource_name == "CVS"))
			continue;

		if (stat(file_resource_path.c_str(), &buf) == 0) {
			// recursively process directories
			if (buf.st_mode & S_IFDIR
				)
				process_directory_recursively(file_resource_path,
						partial_directory_name + "$" + file_resource_name);
			else {
				++file_num;
				// the cout below should give nice animation
				if (((int) (100
						- 100 * ((float) file_num / _num_total_files_to_process))
						% 10) == 0) {
					cout
							<< "\r"
							<< setw(6)
							<< setprecision(3)
							<< (100
									- 100
											* ((float) file_num
													/ _num_total_files_to_process))
							<< setw(25) << " percent remaining..." << " [ "
							<< meter[file_num % 4] << " ] ";
				}
				cout << "\r";

				process_file(file_resource_path, partial_directory_name);
			}
		}
	}

	closedir(dirp);
	status = true;

	return status;
}

/**
 * @brief
 * @param filename
 * @return
 */
bool CDocumentProcessor::process_file(string filename,
		string file_category_identification_string) {
	bool status = false;
	cout << "Processing file " << filename << " ... ";
	string doc_major_category = get_doc_major_category(
			file_category_identification_string);
	//getting the doc name//
	 int byte_offset = filename.find_last_of('/');
	// string res = filename.substr(pos+1);
     ofstream file_ofs;
	CDocument doc(filename);
	doc.set_doc_class_type(_doc_major_category_map[doc_major_category]);
	std::map<size_t,size_t>::iterator file_it;
	//adding into file dict
        file_dict[doc.get_docID()] = byte_offset+1;

            if(file_dict.size()==10000)
            {
            	file_ofs.open(((CUtilities::dir_path)+"/FileDictionary.txt").c_str(),fstream::app);


                for(file_it = file_dict.begin(); file_it!= file_dict.end(); ++file_it) {

                	file_ofs << (*file_it).first << "," << _barrel_id << "," << (*file_it).second <<"$ ";
                }
                ++_barrel_id;
                file_dict.clear();
            }

 	if (b_verbose_global)
		cout << doc.to_string() << endl;


	CBaseParser* parser = _doc_parser_map[doc_major_category];
	parser->parse_document(doc);
	//cout<<"the tokens are for doc:"<<doc.get_docID()<<endl;
    // cout<<"The author ids for doc are:"<<endl;
    InvertedIndexer indexer;
	indexer.addDocument(&doc);

    //std::set<string>::iterator set_itr;
//   for(set_itr = doc.get_raw_token_list().begin();set_itr != doc.get_raw_token_list().end();++set_itr)
  //  	cout<<"Token:"<<*set_itr<<endl;


	status = true;

	return status;
}

/**
 * @brief
 * @param file_category_identification_string
 * @return
 */
string CDocumentProcessor::get_doc_major_category(string file_category_identification_string) {
	size_t pos;

	CUtilities::to_lower(file_category_identification_string);
	pos = file_category_identification_string.find("$wiki");
	if (pos != string::npos)
		return "wiki";
	else {
		pos = file_category_identification_string.find("$news");
		if (pos != string::npos)
			return "news";
	}

	return "other";
}

