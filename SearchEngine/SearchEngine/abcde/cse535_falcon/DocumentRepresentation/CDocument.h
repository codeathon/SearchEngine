/*
 * CDocument.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef CDOCUMENT_H_
#define CDOCUMENT_H_

#include "../include/includes.h"
#include "../TokenProcessor/CBasicTokenProcessor.h"

//typedef pair<string, int> docname_freq;

class CToken;		// incomplete definition
class CTokenList;	// incomplete definition

/**
 * @brief
 */
class CDocument {

protected:
	std::string _resource_name;
	std::string _doc_name;
	size_t _doc_classification_type;
	std::map<std::string, std::string> _doc_feature_map;
    static size_t _globalDocId;
    size_t _docId;
	CTokenList* _p_token_list;
	std::vector<std::string> _raw_tokens_list;
	std::vector<std::string>_normal_token_list;

public:
	CDocument(std::string resource_name = "");
	virtual ~CDocument();
	//static std::map<std::string,size_t> _normal_token_id_map;
	    static std::map<std::string,std::string> _raw_normal_map;
	    static std::map<std::string,size_t> _raw_token_id_map;
	    static std::map<std::string,size_t> term_dict;

	    static std::map<std::string,std::map<std::string, int> > term_cnt_dict;

	    static std::map<std::string,int>doc_name_doc_id;

	    static size_t _normal_id;
	    static size_t _raw_token_id;
	   //document specific author ids and category ids

	    std::vector<size_t>_author_ids;
	   	std::vector<size_t>_category_ids;



	/**
	 * @brief
	 * @return a reference to the document's token list
	 */

	inline std::string get_doc_name() const { return _doc_name; }
	//std::vector<CToken*> get_tokens(){return _tokens_list;}
	std::vector<std::string>& get_raw_token_list(){return _raw_tokens_list;}
	std::vector<std::string>& get_normal_token_list(){return _normal_token_list;}
	static std::map<std::string,size_t>& get_raw_token_id_map(){return _raw_token_id_map;}
    //static std::map<std::string,size_t>& get_normal_token_id_map(){return _normal_token_id_map;}
	static std::map<std::string,std::string>& get_raw_normal_map(){return _raw_normal_map;}
	std::vector<size_t>& get_category_ids(){return _category_ids;}
	std::vector<size_t>& get_author_ids(){return _author_ids;}

	void process_token_list(CBasicTokenProcessor& cbtp, CDocument& doc);

	inline size_t get_docID(){return _docId;}


	inline CTokenList* get_token_list() const { return _p_token_list; }
	/**
	 * @brief
	 * @return
	 */
	inline size_t get_doc_class_type() const { return _doc_classification_type; }
	/**
	 * @brief
	 * @return
	 */
	inline std::string get_resource_name() const { return _resource_name; }
	/**
	 * @brief
	 * @return
	 */
	inline std::map<std::string, std::string> const & get_feature_map() const { return _doc_feature_map; }
	/**
	 * @param doc_class_type
	 */
	inline void set_doc_class_type(size_t doc_class_type) { _doc_classification_type = doc_class_type; }
	/**
	 * @brief
	 * @param token
	 * @return
	 */

	inline void set_doc_name(std:: string doc_name) {_doc_name = doc_name; }

	void add_normal_token(std:: string token) { _normal_token_list.push_back(token); }


	bool add_token(std::string token);
	/**
	 * @brief
	 * @param token
	 * @return
	 */
	bool delete_token(std::string token);
	/**
	 * @brief
	 */
	void process_token_list(CBasicTokenProcessor& token_processor);
	/**
	 * @brief
	 * @return a string representation of the document
	 */
	std::string to_string();
};

/**
 * @brief
 */
class CToken {
	std::string _token_raw_string;
	std::string _token_normal_form;
	std::map<std::string, std::string> _token_feature_map;
	CTokenList *_p_child_token_list;
	CTokenList *_p_current_token_list;
	CToken *_p_parent_token;

public:
	/**
	 * @brief
	 * @param p_current_token_list
	 */
	//CToken(std::string token = "", CTokenList* p_current_token_list = 0);

	CToken(std::string token = "");

public:
	/**
	 * @brief
	 * @return
	 */
	inline std::string get_token_raw_string() const { return _token_raw_string; }
	/**
	 * @brief
	 * @return
	 */
	inline std::string get_token_normal_string() const { return _token_normal_form; }
	/**
	 * @brief
	 * @return
	 */
	inline std::map<std::string, std::string> const & get_feature_map() const { return _token_feature_map; }
	/**
	 * @brief
	 * @return
	 */
	inline CTokenList* get_child_token_list() const { return _p_child_token_list; }
	/**
	 * @brief
	 * @return
	 */
	inline CTokenList* get_current_token_list() const { return _p_current_token_list; }
	/**
	 * @brief
	 * @return
	 */
	inline CToken* get_parent_token() const { return _p_parent_token; }
	/**
	 * @brief
	 * @param normal_string
	 */
	inline void set_token_normal_string(std::string normal_string) { _token_normal_form = normal_string; }
	/**
	 * @brief
	 * @param key
	 * @param value
	 */
	inline void add_feature(std::string key, std::string value) { _token_feature_map[key] = value; }

};

/**
 * @brief
 */
class CTokenList {
	std::list<CToken*>* _p_token_list;
public:
	CTokenList();
	~CTokenList();

	// write down the copy constructors and the assignment operators here
	// CTokenList(CTokenList& a_list);
	// CTokenList& operator=(CTokenList& a_list);

	inline std::list<CToken*>* get_token_list() const { return _p_token_list; }

	/**
	 * @ destroy the token list
	 */
	void destroy_token_list(std::list<CToken*> *head);

	/**
	 * @brief
	 * @param token
	 * @return
	 */
	bool add_token(std::string token);
	/**
	 * @brief
	 * @param token
	 * @return
	 */
	bool delete_token(std::string token);
	/**
	 * @brief
	 * @param p_token
	 * @param splitter_string
	 * @return
	 */
	bool split_token(CToken* p_token, std::string splitter_string);

};


#endif /* CDOCUMENT_H_ */
