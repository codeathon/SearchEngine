/*
 * CDocumentProcessor.h
 *
 *  Created on: Sep 6, 2010
 *      Author: data
 */

#ifndef CDOCUMENTPROCESSOR_H_
#define CDOCUMENTPROCESSOR_H_

#include "../include/includes.h"
#include "../DocumentParsers/CBaseParser.h"

class CDocumentProcessor {

	size_t _num_total_files_to_process;
	size_t _global_file_id;

	std::map<std::string, size_t> _doc_major_category_map;
	std::map<std::string, CBaseParser*> _doc_parser_map;

public:
	CDocumentProcessor();
	virtual ~CDocumentProcessor();
	inline size_t get_num_files_to_process() const {return _num_total_files_to_process; }

	bool count_files_to_process(std::string base_directory_path);
	bool process_directory(std::string directory_path);
	bool process_file(std::string filename, std::string file_category_identification_string);
    static std::map<size_t,size_t>file_dict;
    static size_t _barrel_id;
protected:
	virtual bool process_directory_recursively(std::string base_directory_path, std::string partial_directory_name = "");
	virtual std::string get_doc_major_category(std::string file_category_identification_string);

};

#endif /* CDOCUMENTPROCESSOR_H_ */
