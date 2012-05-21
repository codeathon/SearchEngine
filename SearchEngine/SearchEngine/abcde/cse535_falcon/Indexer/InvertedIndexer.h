/*
 *	File: InvertedIndexer.h
 *	Version: 1.0
 *	Desc:
 *	History:
 *	1. 2011-09-23, Created, Jun Wu
 */

#ifndef INVERTEDINDEXER_H_
#define INVERTEDINDEXER_H_

#include "../include/includes.h"
#include "../DocumentRepresentation/CDocument.h"

using namespace std;

class InvertedIndexer {
private:
	static size_t _barrel_no;
	static size_t _partition_size;
	static size_t _partition_no;
	static size_t _raw_posting_list_size;
	static size_t _partition_max_size;
	static size_t _posting_list_max_size;
	static string _inv_index_folder;
	static multimap<size_t, size_t> _raw__posting_list_map;
	static map<size_t, set<size_t> > _posting_list_map;

public:
	InvertedIndexer();
	InvertedIndexer(string &inv_index_folder, size_t _partition_size, size_t posting_list_max_size);
	virtual ~InvertedIndexer();

	bool addDocument(CDocument *doc);
	void merge(size_t indexBarrelNo, vector<string> indexPartitionSet);
};

#endif /* INVERTEDINDEXER_H_ */
