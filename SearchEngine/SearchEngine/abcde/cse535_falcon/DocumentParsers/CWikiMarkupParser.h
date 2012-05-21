/*
 * CWikiMarkupParser.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef CWIKIMARKUPPARSER_H_
#define CWIKIMARKUPPARSER_H_

#include "../include/includes.h"
#include "../include/CUtilities.h"
#include "CBaseParser.h"

class CParserState;
class CWikiLinkBeginState;
class CWikiLinkEndState;
class CWikiCharacterConsumeState;
class CWikiPartialTagState;
class CWikiSectionBeginState;
class CWikiSectionEndState;
class CWikiInfoBoxBeginState;


//bool sectin_seen;
/**
 * @brief Wiki markup parser
 */
class CWikiMarkupParser : public CBaseParser {

	CParserState* _parser_state;
	CParserState* _parser_previous_state;
	CWikiLinkBeginState* _parser_wlb_state;
	CWikiLinkEndState* _parser_wle_state;
	CWikiCharacterConsumeState* _parser_cc_state;
	CWikiPartialTagState* _parser_pt_state;
	CWikiSectionBeginState* _parser_wsb_state;
	CWikiSectionEndState* _parser_wse_state;
	CWikiInfoBoxBeginState* _parser_wib_state;



	std::set<std::string> _outgoing_link_set;
	std::map<std::string,std::string> _wiki_doc_sect_map;
	std ::list<std::string>_section_header;
	std::list<std::string>_section_details;
    std::set<std::string>_infobox_details;
    std::set<std::string> _authors;
    std::string _timestamp;
    int _semwiki_wiki_id;
    std::string _article_title;
    std::set<std::string> _categories;

    static int _category_id;
    static int _author_id;

	static CWikiMarkupParser* _wiki_markup_parser;

	CWikiMarkupParser();

	bool parse(std::string file_contents);

public:
	  static std::map<std::string,int>_category_map;
	    static std::map<std::string,int>_author_map;
		static std::multimap<std::string,std::string> _link_set_map;
	/**
	 * @brief static
	 */
	inline static CBaseParser* get_instance() {
		if ( _wiki_markup_parser == 0 )
			_wiki_markup_parser = new CWikiMarkupParser();

		return _wiki_markup_parser;
	}

	virtual ~CWikiMarkupParser();

	bool parse_document(CDocument& doc);

	// state functions
	void reset();
	CParserState * get_initial_state() { return _parser_state; }
	CParserState * get_parser_previous_state() { return _parser_state; }
	CParserState * get_wiki_link_begin_state() { return reinterpret_cast<CParserState*>(_parser_wlb_state); }
	CParserState * get_wiki_link_end_state() { return reinterpret_cast<CParserState*>(_parser_wle_state); }
	CParserState * get_wiki_character_consume_state() { return reinterpret_cast<CParserState*>(_parser_cc_state); }
	CParserState * get_wiki_partial_tag_state() { return reinterpret_cast<CParserState*>(_parser_pt_state); }
	CParserState * get_wiki_section_end_state() { return reinterpret_cast<CParserState*>(_parser_wse_state); }
	CParserState * get_wiki_section_begin_state() { return reinterpret_cast<CParserState*>(_parser_wsb_state); }
	CParserState * get_wiki_infobox_begin_state(){ return reinterpret_cast<CParserState*>(_parser_wib_state); }


	void set_state(CParserState* parser_state) { _parser_state = parser_state; }
	void set_prev_state(CParserState* parser_state) { _parser_previous_state = parser_state; }

	std::set<std::string>& get_outgoing_link_set() { return _outgoing_link_set; }
	std::list<std::string>& get_section_header() { return _section_header; }
	std::list<std::string>& get_section_details() { return _section_details; }
	std::set<std::string>& get_infobox_data(){ return _infobox_details;}
	std::set<std::string>& get_authorrs(){return _authors;}
	std::string& get_timestamp(){return _timestamp;}
    std::string& get_article_title(){return _article_title;}
    std::set<std::string>& get_categories(){return _categories;}
    std::multimap<std::string,std::string>& get_link_set(){return _link_set_map;}
	//std::map<std::string,std::string>& get_section_details(){return _wiki_doc_sect_map;}
};

/**
 * @brief State based parser
 */
class CParserState {

protected:
	std::string _buffer;
	CWikiMarkupParser* _parser;

public:
	std::string const & get_string_buffer() const { return _buffer; }

	CParserState();
	virtual void execute(std::string& buffer, size_t consume_index);
};

/**
 * @brief
 */
class CWikiLinkBeginState : public CParserState {

public:
	CWikiLinkBeginState(CWikiMarkupParser *parser);
	void execute(std::string& buffer, size_t consume_index);
};

class CWikiSectionBeginState : public CParserState {

public:
	CWikiSectionBeginState(CWikiMarkupParser *parser);
	void execute(std::string& buffer, size_t consume_index);
};

class CWikiInfoBoxBeginState : public CParserState {

public:
	CWikiInfoBoxBeginState(CWikiMarkupParser *parser);
	void execute(std::string& buffer, size_t consume_index);
};

/**
 * @brief
 */
class CWikiLinkEndState : public CParserState {

public:
	CWikiLinkEndState(CWikiMarkupParser *parser);
	void execute(std::string& buffer, size_t consume_index);
};
class CWikiSectionEndState : public CParserState {

public:
	CWikiSectionEndState(CWikiMarkupParser *parser);
	void execute(std::string& buffer, size_t consume_index);
};


/**
 * @brief
 */
class CWikiCharacterConsumeState : public CParserState {
	bool _b_wiki_link_seen;
	bool _b_section_seen;
	bool _b_infobox_seen;
	bool _b_sub_section_seen;

public:
	CWikiCharacterConsumeState(CWikiMarkupParser *parser);
	void execute(std::string& buffer, size_t consume_index);
	std::string& get_buffer() { return _buffer; }
	void set_buffer(std::string& str) { _buffer = str; }

	bool get_b_wiki_link_seen() { return _b_wiki_link_seen; }
	bool get_b_section_seen() { return _b_section_seen; }
	bool get_b_infobox_seen() { return _b_infobox_seen; }
	bool get_b_sub_section_seen(){return _b_sub_section_seen;}

	void set_b_wiki_link_seen(bool val) { _b_wiki_link_seen = val; }
	void set_b_section_seen(bool val) { _b_section_seen = val; }
	void set_b_infobox_seen(bool val) { _b_infobox_seen = val; }
	void set_b_sub_section_seen(bool val) { _b_sub_section_seen = val;}
};

/**
 * @brief
 */
class CWikiPartialTagState : public CParserState {

public:
	CWikiPartialTagState(CWikiMarkupParser *parser);
	void execute(std::string& buffer, size_t consume_index);
};

#endif /* CWIKIMARKUPPARSER_H_ */
