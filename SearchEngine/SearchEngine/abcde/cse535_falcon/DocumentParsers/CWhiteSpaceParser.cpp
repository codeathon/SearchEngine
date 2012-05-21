/*
 * CWhiteSpaceParser.cpp
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#include "CWhiteSpaceParser.h"
using namespace std;

CWhiteSpaceParser::CWhiteSpaceParser() {

}

CWhiteSpaceParser::~CWhiteSpaceParser() {

}

CWhiteSpaceParser* CWhiteSpaceParser::_white_space_parser = 0;

/**
 * @brief
 * @param filename
 * @return
 */
bool CWhiteSpaceParser::parse_document(CDocument& doc) {
	bool status = false;
	cout << "Parsing news or any other document using simple whitespace tokenization" << endl;

	string file_contents = "";
	string line;
	vector<string> token_vec;
	string delim = "\r\n\t ";

	string filename = doc.get_resource_name();

	ifstream ifs(filename.c_str());
	if ( ifs.is_open() ) {

		while ( !ifs.eof() ) {
			getline( ifs, line );
			file_contents += line;
			file_contents+='\n';
		}

		CUtilities::tokenize(file_contents, token_vec, delim);
		vector<std::string>::iterator raw_token_it;
		//CUtilities::remove_duplicates(token_vec);
		CBasicTokenProcessor* cbtp = new CBasicTokenProcessor();
			for(raw_token_it = token_vec.begin();raw_token_it!=token_vec.end();++raw_token_it)
		{
//          cout<<"Token:"<<*raw_token_it<<endl;
		if(CDocument::_raw_token_id_map.find((*raw_token_it))==CDocument::_raw_token_id_map.end())
			CDocument::_raw_token_id_map[(*raw_token_it)]=CDocument::_raw_token_id++;
		doc.add_token(*raw_token_it);

		}

		doc.process_token_list(*cbtp, doc);
        std::set<string>::iterator saw_token_it;
		//for(saw_token_it = doc.get_normal_token_list().begin();saw_token_it!=doc.get_normal_token_list().end();++saw_token_it)
//		{
	//		cout<<"normalized:"<<(*saw_token_it)<<endl;
		//}


		//cout << "Total number of raw tokens = " << token_vec.size() << endl;
		token_vec.clear();
	} else {
		cout << "Couldn't open file " << filename << endl;
	}

	ifs.close();
	status = true;

	return status;
}
