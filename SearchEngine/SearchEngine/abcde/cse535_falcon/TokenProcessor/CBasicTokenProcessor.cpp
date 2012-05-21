/*
 * CBasicTokenProcessor.cpp
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#include "../include/includes.h"
#include "../include/stemmer.h"
#include "../include/CUtilities.h"
#include "CBasicTokenProcessor.h"
using namespace std;

CBasicTokenProcessor::CBasicTokenProcessor() {

}

CBasicTokenProcessor::~CBasicTokenProcessor() {

}

string CBasicTokenProcessor::process_token(string token) {
	//CBasicEnglishTokenProcessor *cbetp = new CBasicEnglishTokenProcessor();
	//std::string normal_token = cbetp->process_token(token);

	if (CUtilities::stop_word_str.find(token) == string::npos) {
	CUtilities::delete_dashes(token);
	CUtilities::delete_character(token,'\'');
	CUtilities::delete_character(token,'/');
	CUtilities::delete_character(token,'$');
	CUtilities::delete_character(token,'<');
	CUtilities::delete_character(token,'>');
	CUtilities::delete_character(token,'(');
	CUtilities::delete_character(token,')');
	CUtilities::delete_character(token,',');
	CUtilities::delete_character(token,'{');
	CUtilities::delete_character(token,'}');
	CUtilities::delete_character(token,'|');
	CUtilities::delete_character(token,'.');
	CUtilities::delete_character(token,'&nbsp');
	CUtilities::delete_character(token,'&');

	CUtilities::delete_non_alphanum_left_right(token);
	CUtilities::to_lower(token); // Prerequisite for Stemming


	char tokenChar[token.length()];
	int i;
	for(i=0;i<=token.length();i++)
	tokenChar[i] = token[i];
	int end_point = stem(tokenChar,0 , token.length()-1);
	string stemmed_token = token.substr(0,end_point+1);

	return stemmed_token; }
	else
	return "";
}
