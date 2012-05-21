/*
 * forwardIndexer.h
 *
 *  Created on: Oct 1, 2011
 *      Author: nishant
 */

#ifndef FORWARDINDEXER_H_
#define FORWARDINDEXER_H_
#include "../DocumentRepresentation/CDocument.h"

namespace std {

class forwardIndexer {
private:
		static string _frwd_index_folder;
protected:
	std::string resource_name;
public:
	static size_t barrel_id;
	size_t file_id;
	static std::multimap<size_t,std::string> forward_index_map;
	static std::vector<size_t> doc_ids;

	forwardIndexer(string &frwd_index_folder);

    bool process_file(string filename);
    bool process_directory(string semwiki_directory_path);
	forwardIndexer();
	virtual ~forwardIndexer();
};

} /* namespace std */
#endif /* FORWARDINDEXER_H_ */
