/*
 * CWikiMarkupParser.cpp
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#include "CWikiMarkupParser.h"
#include<sstream>
#include<string>
using namespace std;

/**
 * @brief constructor
 */
CWikiMarkupParser::CWikiMarkupParser() {
	CParserState* _parser_state = new CParserState();
	_parser_previous_state = _parser_state;
	_parser_wlb_state = new CWikiLinkBeginState(this);
	_parser_wle_state = new CWikiLinkEndState(this);
	_parser_cc_state = new CWikiCharacterConsumeState(this);
	_parser_pt_state = new CWikiPartialTagState(this);
	_parser_wsb_state = new CWikiSectionBeginState(this);
	_parser_wse_state = new CWikiSectionEndState(this);
	_parser_wib_state = new CWikiInfoBoxBeginState(this);
	_authors.clear();
	_categories.clear();

}

/**
 * @brief destructor
 */
CWikiMarkupParser::~CWikiMarkupParser() {
	delete _parser_cc_state;
	delete _parser_wlb_state;
	delete _parser_wle_state;
	delete _parser_pt_state;
	delete _parser_state;
	delete _parser_wse_state;
	delete _parser_wsb_state;
	delete _parser_wib_state;
}

CWikiMarkupParser* CWikiMarkupParser::_wiki_markup_parser = 0;
std::map<std::string,int> CWikiMarkupParser::_category_map;
int CWikiMarkupParser::_category_id = 0;
std::map<std::string,int>CWikiMarkupParser::_author_map;
int CWikiMarkupParser::_author_id=0;
std::multimap<std::string,std::string>CWikiMarkupParser ::_link_set_map;
//int CWikiMarkupParser::_

/**
 * @brief
 * @param filename
 * @return
 */
bool CWikiMarkupParser::parse_document(CDocument& doc) {
	bool status = false;
	cout << "Parsing Wiki markup document using a state based tag parser" << endl;

    stringstream oss;
	string file_contents = "";
	string line;
	string line2;
	vector<string> token_vec;
	string delim = "\r\n\t ";
	string filename = doc.get_resource_name();
	string sem_wiki_fname;
	int doc_id;
	doc_id=doc.get_docID();
//	cout<<"Doc_id:"<<doc_id;
	oss<<doc_id;
	std::string path;
	path=CUtilities::semwiki_dir_path+"/";

	sem_wiki_fname=path+oss.str()+"_semwiki.txt";
	//cout<<"the path for semwiki file is:"<<sem_wiki_fname<<endl;
    _semwiki_wiki_id = doc_id;
    int pos = filename.find_last_of('/');

    string res = filename.substr(pos+1);
    int txt_loc = res.find(".txt");

     _article_title = res.substr(0,txt_loc);

	ifstream ifs(filename.c_str());
	if ( ifs.is_open() )
	{

		while ( !ifs.eof() )
		{
			getline( ifs, line );
			file_contents += line+' ';
			if(line.find("<<Author>>")!=string::npos)
			{
				string aut;
				istringstream liness(line);
				getline(liness,aut,':');
				getline(liness,aut,'\n');
				 pos = aut.find(',');


				if(pos==string::npos)
					_authors.insert(aut);
				else
				{
				string final_authors;
				string rem_stuff;
				while(pos!=string::npos)
				{
	//				cout<<"inside while:"<<aut<<endl;
					final_authors = aut.substr(0,pos);
		//			cout<<"final authors:"<<final_authors<<endl;
					rem_stuff = aut.substr(pos+1);
	//			cout<<"rem_stuff:"<<rem_stuff<<endl;
		    		_authors.insert(final_authors);
				    pos =rem_stuff.find(',');
				    aut=rem_stuff;
				    if(pos==string::npos)
				    {
				    	_authors.insert(rem_stuff);
				    	break;
				    }

				}

			}
			}
			if(line.find("<<Timestamp>>")!=string::npos)
						{
							string timestp;
							istringstream liness(line);
							getline(liness,timestp,':');
							getline(liness,timestp,'\n');

							_timestamp = timestp;
						}
		}


	}
	else
	{
		cout << "Couldn't open file " << filename << endl;
	}

	ifs.close();

	// start parsing the file_contents
	cout << "file contents size = " << file_contents.size() << endl;

	status = parse(file_contents);
	ofstream ofs;
	ofs.open(sem_wiki_fname.c_str(),ios::trunc);
	ofs<<"<<#WikiFileId>>\n";
	ofs<<_semwiki_wiki_id<<"\n";
	ofs<<"<<#Article Title>>\n";
	ofs<<_article_title<<"\n";
	ofs<<"<<#Author>>\n";
	std::set<std::string>::iterator ait;
	for(ait=_authors.begin();ait!=_authors.end();++ait)
	{

		if (_author_map.find(*ait)==_author_map.end())
					_author_map[*ait]=++_author_id;
	ofs<<(*ait)<<" $ ";
	doc._author_ids.push_back(_author_map[*ait]);
	}
	ofs<<"\n<<#Timestamp>>\n";
	ofs<<_timestamp<<"\n";
	ofs<<"<<#Infobox>>\n";
	set<string>::iterator i_itr;
	for ( i_itr = _infobox_details.begin(); i_itr != _infobox_details.end(); ++i_itr)
	{
		ofs<<*i_itr;
	}

	ofs<<"\n<<#Sections>>\n";

	list<string>::iterator sec_itr;
	list<string>::iterator sec_det_itr;
	string temp1="";
	for(sec_itr=_section_header.begin(),sec_det_itr=_section_details.begin();sec_itr!=_section_header.end()&&sec_det_itr!=_section_details.end();++sec_itr,++sec_det_itr)
	{
		temp1=*sec_itr+"  $";
		ofs<<temp1;
		ofs<<(*sec_det_itr);
        ofs<<"\n";
	}
	ofs<<"<<#LINKS>>"<<"\n";
     string temp ="";
	set<string>::iterator s_itr;
	size_t link_counter = 1;
	for ( s_itr = _outgoing_link_set.begin(); s_itr != _outgoing_link_set.end(); ++s_itr, link_counter++ )
	{
		//cout << "linking to ==> (#" << link_counter << ") " << *s_itr << endl;
		temp=*s_itr+" $";
		ofs<<temp;
		_link_set_map.insert(pair<std::string,std::string>(_article_title,temp));
		temp="";
	}
	ofs<<"\n<<#Categories>>\n";
	map<string,int>::iterator cat_map;
	set<string>::iterator cat;
	for(cat = _categories.begin();cat!=_categories.end();++cat)
	{
		if (_category_map.find(*cat)==_category_map.end())
			_category_map[*cat]=++_category_id;
		ofs<<*cat<<" $ ";
		doc._category_ids.push_back(_category_map[*cat]);
	}

ofs.close();
_authors.clear();
	_categories.clear();
	_timestamp = "";
CUtilities::tokenize(file_contents, token_vec, delim);
//cout << "Total number of raw tokens = " << token_vec.size() << endl;
vector<std::string>::iterator raw_token_it;
CBasicTokenProcessor* cbtp = new CBasicTokenProcessor();
for(raw_token_it = token_vec.begin();raw_token_it!=token_vec.end();++raw_token_it)
	{
      //cout<<"Token:"<<*raw_token_it<<endl;
	if(CDocument::_raw_token_id_map.find((*raw_token_it))==CDocument::_raw_token_id_map.end())
		CDocument::_raw_token_id_map[(*raw_token_it)]=CDocument::_raw_token_id++;
	doc.add_token(*raw_token_it);

	}

	doc.process_token_list(*cbtp, doc);
token_vec.clear();

return status;
}

/**
 * @brief
 * @param file_contents
 */
bool CWikiMarkupParser::parse(std::string file_contents) {
	bool status = false;
	//cout<<"inside cwikimarkupparsaer parse"<<endl;
	// reset the parser for each wiki file parsed
	reset();


	// start parsing from the beginning of the string buffer
	size_t beg_pos = 0;
	size_t end_pos = file_contents.length();
	// put the parser in the character consume state
	_parser_state = _parser_cc_state;
	for ( size_t i = beg_pos; i < end_pos; ++i ) {
		_parser_state->execute(file_contents, i);
	}

	status = true;
	return status;
}

/**
 * @brief resets the parser state
 */
void CWikiMarkupParser::reset() {
	_parser_state = _parser_cc_state;
	_outgoing_link_set.clear();
	_section_details.clear();
	_section_header.clear();
	_infobox_details.clear();

}

/**
 * @brief constructor
 * @param parser
 */
CParserState::CParserState() {
	_buffer = "";
}

/**
 * @brief execute the parser based on the state that called this method
 * @param buffer
 * @param consume_index
 */
void CParserState::execute(string& buffer, size_t consume_index) {
	// do nothing for now

}

/**
 * @brief constructor
 * @param parser
 */
CWikiCharacterConsumeState::CWikiCharacterConsumeState(CWikiMarkupParser *parser) {
	CParserState::_parser = parser;
	_buffer = "";
}

/**
 * @brief execute the parser based on the state that called this method
 */
void CWikiCharacterConsumeState::execute(string& buffer, size_t consume_index) {
	//cout<<"inside character consume state execute bverbose:"<<b_verbose_global<<" buffer:"<<_buffer<<endl;
	//cout<<"buffer[index]:"<<buffer[consume_index]<<"link seen:"<<_b_wiki_link_seen<<endl;
	if ( b_verbose_global ) cout << "cc_state: " << _buffer << endl;
	if ( b_verbose_global ) {
		if ( _b_wiki_link_seen ) cout << "cc s wiki_link = true: " << endl; else cout << "cc s wiki_link = false: " << endl;
	}

	switch (buffer[consume_index]) {
	case '[':
		_parser->set_state(_parser->get_wiki_partial_tag_state());
		break;
	case ']':
		_parser->set_state(_parser->get_wiki_partial_tag_state());
		break;
	case '|':

		if ( _b_wiki_link_seen ) {
			if ( b_verbose_global) cout << "cc s | : " << _buffer << endl;	// TODO-remove
              if(buffer[consume_index+1]==']'&&buffer[consume_index+2]==']')
              {
			_parser->get_outgoing_link_set().insert(_buffer);
			_b_wiki_link_seen = false;
              }
			//_parser->set_state(_parser->get_wiki_link_end_state());
			//_parser->set_state(_parser->get_wiki_partial_tag_state());
		} else
			_parser->set_state(_parser->get_wiki_character_consume_state());
		break;
	case '=' :
		_parser->set_state(_parser->get_wiki_partial_tag_state());
		break;
	case '{':
			_parser->set_state(_parser->get_wiki_partial_tag_state());
			break;
	default:
		_buffer += buffer[consume_index];
		break;
	}
	//cout<<"left the consumestate execute"<<endl;
}

/**
 * @brief constructor
 * @param parser
 */
CWikiLinkBeginState::CWikiLinkBeginState(CWikiMarkupParser *parser) {
	CParserState::_parser = parser;
}
CWikiSectionBeginState::CWikiSectionBeginState(CWikiMarkupParser *parser)
{
	CParserState::_parser = parser;
}

CWikiInfoBoxBeginState::CWikiInfoBoxBeginState(CWikiMarkupParser *parser) {
	CParserState::_parser = parser;
}

/**
 * @brief execute the parser based on the state that called this method
 */
void CWikiLinkBeginState::execute(string& buffer, size_t consume_index) {
//cout<<"inside cwikilimkbeginstate execute buffer[consume]:"<<buffer[consume_index];
	switch (buffer[consume_index]) {
	case '[':	// this is the third '[' in sequence - don't do anything

		break;
	case ']' :
		_parser->set_state(_parser->get_wiki_partial_tag_state());
		break;
	case '|' :
		_parser->set_state(_parser->get_wiki_partial_tag_state());
		break;
	default:
		int i;
		string compare ="";
        for(i=consume_index;i<consume_index+9;i++)
        	compare+=buffer[i];
        //cout<<"category:"<<compare<<endl;
        if(compare=="Category:")

        {
        	compare = "";
        	for(;buffer[i]!=']'&& buffer[i]!='|';i++)
        		compare+=buffer[i];
        	//cout<<"category2:"<<compare<<endl;
        	_parser->get_categories().insert(compare);

        }
		CWikiCharacterConsumeState* state = reinterpret_cast<CWikiCharacterConsumeState*>(_parser->get_wiki_character_consume_state());
		state->set_b_wiki_link_seen(true);
		string temp_str(1, buffer[consume_index]);
	//	cout<<"Begin state temp_str:"<<temp_str;
		if ( b_verbose_global ) cout << "consume_index = " << consume_index << endl; //TODO--remove
		if ( b_verbose_global ) cout << "wlb s: " << temp_str << endl; // TODO remove
		state->set_buffer(temp_str);
		_parser->set_state(state);
		break;
	}
}

void CWikiSectionBeginState::execute(string & buffer,size_t consume_index)
{
	CWikiCharacterConsumeState* state = reinterpret_cast<CWikiCharacterConsumeState*>(_parser->get_wiki_character_consume_state());
	//cout<<"inside begin"<<endl;
	switch (buffer[consume_index]) {
	case '=':	// this case can be used to write a map for sublinks
		//_parser->set_state(_parser->get_wiki_character_consume_state());

				state->set_b_sub_section_seen(true);
		break;
	default:


		state->set_b_section_seen(true);
		//sectin_seen = true;
		string temp_str(1, buffer[consume_index]);
	//	cout<<"Begin state temp_str:"<<temp_str;
		//if ( b_verbose_global ) cout << "consume_index = " << consume_index << endl; //TODO--remove
		//if ( b_verbose_global ) cout << "wlb s: " << temp_str << endl; // TODO remove
		state->set_buffer(temp_str);
		_parser->set_state(state);
		break;
	}

}

void CWikiInfoBoxBeginState::execute(string& buffer, size_t consume_index) {
//cout<<"inside infobox buffer[consume]:"<<buffer[consume_index]<<endl;
	switch (buffer[consume_index]) {
	case '{':	// this is the third '[' in sequence - don't do anything

		break;
	case '}' :
		_parser->set_state(_parser->get_wiki_partial_tag_state());
		break;

	default:
        std::string info_box_str="";
        for(int i = 0;i<=6;i++)
        	info_box_str+=tolower(buffer[consume_index+i]);

        if(info_box_str=="infobox")

        {
        	info_box_str+="{{";
        //	cout<<"inside the if for infobox"<<endl;
        	std::string infobox_content="";
        	for(int i=0;buffer[consume_index+i]!='}'&& buffer[consume_index+1]!='}';i++)
        	{
        		if(buffer[consume_index+i]=='\0')
        			break;
        		if(buffer[consume_index+i+1]=='|')
        			infobox_content+="\n";
        		infobox_content+=buffer[consume_index+i];
        	}
        	infobox_content+="\n}}";
		CWikiCharacterConsumeState* state = reinterpret_cast<CWikiCharacterConsumeState*>(_parser->get_wiki_character_consume_state());
		state->set_b_infobox_seen(true);
		_parser->get_infobox_data().insert(infobox_content);
		string temp_str(1, buffer[consume_index]);
		if ( b_verbose_global ) cout << "consume_index = " << consume_index << endl; //TODO--remove
		if ( b_verbose_global ) cout << "wlb s: " << temp_str << endl; // TODO remove
		state->set_buffer(temp_str);
		_parser->set_state(state);
        }
		break;
	}
}


/**
 * @brief constructor
 * @param parser
 */
CWikiLinkEndState::CWikiLinkEndState(CWikiMarkupParser *parser) {
	CParserState::_parser = parser;
}
CWikiSectionEndState::CWikiSectionEndState(CWikiMarkupParser *parser)
{
	CParserState::_parser = parser;
}



/**
 * @brief execute the parser based on the state that called this method
 */
void CWikiLinkEndState::execute(string& buffer, size_t consume_index) {
    //cout<<"inside end"<<endl;
	//cout<<"inside cwikilink end state execute. buffer[consume]:"<<buffer[consume_index]<<endl;
	switch (buffer[consume_index]) {
	case '[':
		_parser->set_state(_parser->get_wiki_link_begin_state());
		break;
	case ']':	// this is the third ']' in sequence - don't do anything
		_parser->set_state(_parser->get_wiki_character_consume_state());
		break;
	default:

		CWikiCharacterConsumeState* state = reinterpret_cast<CWikiCharacterConsumeState*>(_parser->get_wiki_character_consume_state());

		if ( state->get_b_wiki_link_seen() ) {
			if ( b_verbose_global ) cout << "wle s: " << state->get_string_buffer() << endl; // TODO remove
			//cout<<"a link is seen and is getting inserted"<<endl;
			_parser->get_outgoing_link_set().insert(state->get_string_buffer());
			state->set_b_wiki_link_seen(false);
		}

		string temp_str(1, buffer[consume_index]);
		state->set_buffer(temp_str);
		_parser->set_state(state);
		break;
	}
}

void CWikiSectionEndState::execute(string & buffer,size_t consume_index)
{
	switch (buffer[consume_index]) {
		case '=':
			//_parser->set_state(_parser->get_wiki_link_begin_state());
			break;
		default:
          // cout<<"inside end ka default"<<endl;
			CWikiCharacterConsumeState* state = reinterpret_cast<CWikiCharacterConsumeState*>(_parser->get_wiki_character_consume_state());

			if ( state->get_b_section_seen()||state->get_b_sub_section_seen())
			{

			     std::string section_details="";
			     int temp=60;
			     for(int i=1;i<temp;i++)
			     {
			    	 if(buffer[consume_index+i]=='\0')
			    		 break;
			    	 if((buffer[consume_index+i]>='a'&& buffer[consume_index+i]<='z')||(buffer[consume_index+i]>='A'&& buffer[consume_index+i]<='Z')||(buffer[consume_index+i]>='0'&& buffer[consume_index+i]<='9')||buffer[consume_index+i]==' '||buffer[consume_index+i]=='\n')

			    		 section_details+=buffer[consume_index+i];
			    	 else
			    		 temp=temp+1;
			     }
			     //cout<<"buferr at +:"<<state->get_buffer()<<"temp:"<<section_details<<endl;
                  std::string section_header_string = "";
                  if(state->get_b_sub_section_seen())
                	  section_header_string += "<<SubSection>>"+ state->get_buffer();
                  else
                	  section_header_string += state->get_buffer();
			     _parser->get_section_header().push_back(section_header_string);
			     _parser->get_section_details().push_back(section_details);

				state->set_b_section_seen(false);
				state->set_b_sub_section_seen(false);


			   }

			string temp_str(1, buffer[consume_index]);
			state->set_buffer(temp_str);
			_parser->set_state(state);
			break;
		}

}



/**
 * @brief constructor
 * @param parser
 */
CWikiPartialTagState::CWikiPartialTagState(CWikiMarkupParser *parser) {
	CParserState::_parser = parser;
}

/**
 * @brief execute the parser based on the state that called this method
 */
void CWikiPartialTagState::execute(string& buffer, size_t consume_index) {

	CWikiCharacterConsumeState* state = reinterpret_cast<CWikiCharacterConsumeState*>(_parser->get_wiki_character_consume_state());
	//cout<<"inside partial tag state buffer:"<<buffer[consume_index]<<endl;
	switch (buffer[consume_index]) {
	case '[':
		_parser->set_state(_parser->get_wiki_link_begin_state());
		break;
	case ']':
		_parser->set_state(_parser->get_wiki_link_end_state());
		break;
	case '=':
		//cout<<"bool:"<<state->get_b_section_seen()<<endl;
		if (state->get_b_section_seen()||state->get_b_sub_section_seen())
		{
             //cout<<"buffer:"<<buffer[consume_index+1]<<endl;
			_parser->set_state(_parser->get_wiki_section_end_state());
		}
		else
			_parser->set_state(_parser->get_wiki_section_begin_state());
		break;

	case '{': _parser->set_state(_parser->get_wiki_infobox_begin_state());
	break;
	default:
		string temp_str(1, buffer[consume_index]);
				state->set_buffer(temp_str);
				_parser->set_state(state);

		break;
	}

}
