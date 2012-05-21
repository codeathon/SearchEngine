/*
 * CDocument.cpp
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#include "CDocument.h"

//typedef pair<std::string, int> docname_freq;

#include "../include/CUtilities.h"
size_t CDocument::_globalDocId = 0;
size_t CDocument ::_normal_id = 0;
size_t CDocument::_raw_token_id = 0;
std :: map<std::string,size_t> CDocument ::_raw_token_id_map;
//std:: map<std::string,size_t>CDocument ::_normal_token_id_map;
std::map<std::string,std::string>CDocument::_raw_normal_map;
std::map<std::string,size_t>CDocument::term_dict;
std::map<std::string, std::map<std::string, int> >CDocument::term_cnt_dict;
std::map<std::string,int>CDocument::doc_name_doc_id;
using namespace std;

/**
 *
 */
CDocument::CDocument(string resource_name ) {
	_p_token_list = new CTokenList();
	_resource_name = resource_name;
	_docId = ++_globalDocId;
	_author_ids.clear();
	_category_ids.clear();
	_doc_name = resource_name;
	doc_name_doc_id[_doc_name]=_docId;
	cout<<"doc :"<<doc_name_doc_id[_doc_name]<<endl;

}

/**
 *
 */
CDocument::~CDocument() {
	delete _p_token_list;
}

/**
 *
 */
bool CDocument::add_token(string token) {
	//return _p_token_list->add_token(token);
	_raw_tokens_list.push_back(token);
}

/**
 *
 */
bool CDocument::delete_token(string token) {
	return _p_token_list->delete_token(token);
}

/**
 * @brief
 * @note This function should do a recursive traversal
 */
void CDocument::process_token_list(CBasicTokenProcessor& token_processor, CDocument& doc) {
	vector<string>::iterator raw_token_it;
	map<string,int> doc_termfreq;
	typedef pair<string,int> docname_freq;
	for (raw_token_it = _raw_tokens_list.begin();raw_token_it!=_raw_tokens_list.end();++raw_token_it)
	{

		std::string temp=token_processor.process_token(*raw_token_it);

		if(temp!="")
		{
			string str = doc._doc_name;
			//term_doc_names.insert(pair<std::string,std::string>(temp,str));

			if(_raw_normal_map.find(*raw_token_it)==_raw_normal_map.end())
				{
				_raw_normal_map[*raw_token_it] = temp;
				doc.add_normal_token(temp);
				//cout<<"if doc_name:" <<doc._doc_name;
				doc_termfreq.insert(pair<string,int>(doc._doc_name,1));
				CDocument::term_cnt_dict.insert(pair<std::string, std::map<std::string, int> >(temp,doc_termfreq));
				CDocument::term_dict[temp]=++_normal_id;
				}

			else
				{    //cout<<"inside else"<<endl;
				// std::string a = _raw_normal_map[*raw_token_it];
					doc_termfreq = CDocument::term_cnt_dict[temp];
					++doc_termfreq[doc._doc_name];
	//				cout << "else doc_name:"<< doc._doc_name<< " Freq: "<< doc_termfreq[doc._doc_name]<<endl;
					CDocument::term_cnt_dict[temp] = doc_termfreq;
		        //int c = term_dict[a];
			//term_cnt_dict[c] = term_cnt_dict[c]+1;
				}
			doc_termfreq.clear();
		}
	}

	cout << "Size of normal token list: " << doc.get_normal_token_list().size();
	return ;
}

/**
 * @brief
 * @return a string representation of the document
 */
string CDocument::to_string() {
	string s = "";
	s += _resource_name + ", ";
	s += CUtilities::number_to_string(_doc_classification_type) + ", [";
	map<string, string>::iterator itr;
	for ( itr = _doc_feature_map.begin(); itr != _doc_feature_map.end(); ++itr )
		s += itr->first + " : " + itr->second + ", ";
	s += "] ";
	return s;
}

/**
 *
 */
//CToken::CToken(std::string token, CTokenList* p_current_token_list)
CToken::CToken(std::string token){
	_token_raw_string = token;
	_token_normal_form = "";
//	CTokenList *_p_child_token_list = 0;
//	CToken *_p_parent_token = 0;
	//_p_current_token_list = p_current_token_list;
}

/**
 *
 */
CTokenList::CTokenList() {
	_p_token_list = new list<CToken*>();
}

/**
 * @brief destructor for CTokenList
 */
CTokenList::~CTokenList() {
	destroy_token_list(_p_token_list);
}

/**
 * @brief destroy the token list
 */
void CTokenList::destroy_token_list(list<CToken*> *head) {
	// do a bfs for complete token list destruction
	list<CToken*>::iterator itr;
	for ( itr = head->begin(); itr != head->end(); ++itr ) {
		if ( (*itr)->get_child_token_list()->get_token_list()->size() != 0 )
			destroy_token_list((*itr)->get_child_token_list()->get_token_list());
		else
			delete *itr;
	}

}

/**
 *
 */
bool CTokenList::add_token(string token) {
	bool status = false;

//	_p_token_list->push_back(new CToken(token, this));
	status = true;
	return status;
}

/**
 *
 */
bool CTokenList::delete_token(std::string token) {
	bool status = false;
	// deleting a token is tricky if its child is not null
	return status;
}

/**
 *
 */
bool CTokenList::split_token(CToken* p_token, std::string splitter_string) {
	bool status = false;
	return status;
}
