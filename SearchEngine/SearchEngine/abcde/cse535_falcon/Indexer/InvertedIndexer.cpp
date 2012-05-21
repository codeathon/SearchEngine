/*
 *	File: InvertedIndexer.cpp
 *	Version: 1.0
 *	Desc:
 *	History:
 *	1. 2011-09-23, Created, Jun Wu
 */

#include "InvertedIndexer.h"
#include "StringHelper.h"
#include "FileHelper.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*************************************
 * Default parameter values.
 * Can be override by constructor
 */
//Counters
size_t InvertedIndexer::_barrel_no = 0;
size_t InvertedIndexer::_raw_posting_list_size = 0;
size_t InvertedIndexer::_partition_no = 0;

//Boundary
size_t InvertedIndexer::_partition_max_size = 300;
size_t InvertedIndexer::_posting_list_max_size = 30;

vector<string> wikiIndexPartitionSet;
multimap<size_t, size_t> InvertedIndexer::_raw__posting_list_map;
map<size_t, set<size_t> > InvertedIndexer::_posting_list_map;
string InvertedIndexer::_inv_index_folder = "/home/jerry/workspace/CSE535_IR/inv_index/term_inv_index";
size_t counter;

map<std::string,size_t> normalDict;

InvertedIndexer::InvertedIndexer() {
	// TODO Auto-generated constructor stub
}

InvertedIndexer::InvertedIndexer(string &inv_index_folder, size_t partition_max_size, size_t posting_list_max_size){
	_inv_index_folder = inv_index_folder;
	_partition_max_size = partition_max_size;
	_posting_list_max_size = posting_list_max_size;
}

InvertedIndexer::~InvertedIndexer() {
	// TODO Auto-generated destructor stub
}

bool InvertedIndexer::addDocument(CDocument *doc){
	bool status = false;
	string indexFileName = "index.inv.";
	char buffer[50];

/*	map<std::string,size_t> normalTokenIdMap = doc->get_normal_token_id_map();
	map<std::string,size_t>::iterator tokenItr;
	cout << "++++++++++++++++++++" << normalTokenIdMap.size() << endl;
	doc->get_normal_token_id_map().clear();

	for(tokenItr=normalTokenIdMap.begin(); tokenItr!=normalTokenIdMap.end(); tokenItr++){
		_raw__posting_list_map.insert(pair<size_t,size_t>(tokenItr->second, doc->get_docID()));
		_raw_posting_list_size++;
	}*/

	vector<string> normalTokens = doc->get_normal_token_list();
	//cout << "++++++++++++++++++++" << normalTokens.size() << endl;
	//normalDict = doc->getTermDic();

	vector<string>::iterator vectorIter;
	for(vectorIter=normalTokens.begin(); vectorIter!=normalTokens.end(); vectorIter++){
		_raw__posting_list_map.insert(pair<size_t,size_t>(StringHelper::toInt(*vectorIter), doc->get_docID()));
		_raw_posting_list_size++;
	}


	cout << "Posting list size:" << _raw__posting_list_map.size() << endl;

	if(_raw_posting_list_size >= _posting_list_max_size){
		// Output to index file

		sprintf (buffer, "%03d", _barrel_no);
		indexFileName.append(buffer);
		indexFileName.append(".");
		sprintf (buffer, "%03d", _partition_no);
		indexFileName.append(buffer);
		string filePath = _inv_index_folder + indexFileName;
		wikiIndexPartitionSet.push_back(filePath);
		string content;

		size_t minTermId = 0;
		set<size_t> posting_list;
		bool firstLoop = true;
		counter = 0;
		multimap<size_t, size_t>::iterator rawindexIterator;
		for(rawindexIterator = _raw__posting_list_map.begin();
				rawindexIterator != _raw__posting_list_map.end();
				rawindexIterator++){

			size_t headTermId = rawindexIterator->first;
			size_t headDocId = rawindexIterator->second;

			if(firstLoop){
				minTermId = headTermId;
				posting_list.insert(headDocId);
				firstLoop = false;
				continue;
			}

			if(headTermId==minTermId){
				posting_list.insert(headDocId);

				if(counter == _raw__posting_list_map.size()){
					_posting_list_map[minTermId] = posting_list;
					posting_list.clear();
				}
			}else if(headTermId > minTermId){
				//Save the constructed term to map for output
				_posting_list_map[minTermId] = posting_list;

				//Set pivot to new values and clear posting list
				posting_list.clear();
				minTermId = headTermId;
				posting_list.insert(headDocId);
			}
		}

		map<size_t, set<size_t> >::iterator indexIterator;
		for(indexIterator = _posting_list_map.begin();
				indexIterator != _posting_list_map.end();
				indexIterator++){
			sprintf (buffer, "%d", indexIterator->first);
			content.append(buffer);
			content.append(",");

			set<size_t> postingListRecord = indexIterator->second;
			set<size_t>::iterator setIterator;
			string postingString;
			counter = 1;
			for(setIterator = postingListRecord.begin();
					setIterator != postingListRecord.end();
						setIterator++){
				sprintf (buffer, "%d", *setIterator);
				postingString.append(buffer);
				if(counter!=postingListRecord.size()){
					postingString.append(":");
					counter++;
				}

			}

			content.append(postingString);
			content.append("\n");
		}

		cout << "Posting list is over " << _posting_list_max_size << ", flush it to index partition file " << filePath << endl;
		FileHelper::writeToFile(filePath, content);
		content.clear();
		_posting_list_map.clear();
		_raw__posting_list_map.clear();
		_raw_posting_list_size = 0;

		if(_partition_no >= _partition_max_size){
			cout << "The number of index partition files exceeds the limitation[" << _partition_max_size << "]. Merge into one index barrel." << endl;
			InvertedIndexer::merge(_barrel_no, wikiIndexPartitionSet);

			_barrel_no++;
			_partition_no = 0;
			wikiIndexPartitionSet.clear();
		}

		_partition_no ++;
	}
	//cout << "Finish index for document " << doc->get_resource_name() << endl;
	return status;
}

void InvertedIndexer::merge(size_t indexBarrelNo, vector<string> indexPartitionSet){
	char temp[100];
	string indexFileName = "index.inv.";
	int fileCount = indexPartitionSet.size();
	string indexSlicePath = _inv_index_folder + indexFileName;
	sprintf (temp, "%03d", indexBarrelNo);
	indexSlicePath.append(temp);
	indexSlicePath.append(".pstngs");
	ofstream finalIndexFile(indexSlicePath.c_str());
	ifstream *indexSlices = new ifstream[fileCount];
	string delim = ":";

	multimap<size_t, set<size_t> > mergeMap;

	for(size_t i=0; i< indexPartitionSet.size(); i++){
		indexSlices[i].open(indexPartitionSet[i].c_str(), ios::in);
	}

	for(int i =0; i < fileCount; i++){

		if(!indexSlices[i].is_open()){
			cout << "Could not open file " << indexPartitionSet[i] << endl;
			continue;
		}

		while(!indexSlices[i].eof()){
			string oneLine;
			size_t mergeTermId;
			set<size_t> mergeDocIds;

			getline(indexSlices[i], oneLine);
			if((oneLine.find_first_of(","))==string::npos){
				cout << "Ignore blank line in the index partition file " << indexPartitionSet[i].c_str() << endl;
				continue;
			}

			size_t commaIndex = oneLine.find_first_of(",");
			mergeTermId = StringHelper::toInt(oneLine.substr(0, commaIndex));
			vector<string> tokens = StringHelper::split(oneLine.substr(commaIndex+1), delim);

			for(vector<string>::iterator itr=tokens.begin(); itr!=tokens.end(); itr++){
				//cout << "post id:" << *itr << endl;
				size_t post_id = StringHelper::toInt(*itr);
				mergeDocIds.insert(post_id);
			}
			mergeMap.insert(pair<size_t,set<size_t> >(mergeTermId, mergeDocIds));
		}
	}

	for(int i=0; i < fileCount; i++)
		indexSlices[i].close();

	delete [] indexSlices;

	for(size_t i=0; i< indexPartitionSet.size(); i++){
		remove(indexPartitionSet[i].c_str());
		cout << "Delete index partition file " << indexPartitionSet[i].c_str() << endl;
	}

	size_t minMergeTermId;
	set<size_t> minMergeDocIds;
	map<size_t, set<size_t> > outMap;
	bool isFirstLoop = true;
	counter = 0;
	multimap<size_t, set<size_t> >::iterator mergeIterator;
	for(mergeIterator=mergeMap.begin(); mergeIterator!=mergeMap.end(); mergeIterator++){
		size_t mergeTermId = mergeIterator->first;
		set<size_t> mergeDocIds = mergeIterator->second;

		counter++;
		if(isFirstLoop){
			minMergeTermId = mergeTermId;
			minMergeDocIds = mergeDocIds;
			isFirstLoop = false;
			continue;
		}

		if(mergeTermId==minMergeTermId){
			for(set<size_t>::iterator itr=mergeDocIds.begin(); itr!=mergeDocIds.end(); itr++){
				minMergeDocIds.insert(*itr);
			}

			if(counter == mergeMap.size()){
				outMap[minMergeTermId] = minMergeDocIds;
				minMergeDocIds.clear();
			}
		}else if(mergeTermId > minMergeTermId){
			//Save the constructed term to map for output
			outMap[minMergeTermId] = minMergeDocIds;

			//Set pivot to new values and clear posting list
			minMergeDocIds.clear();
			minMergeTermId = mergeTermId;
			minMergeDocIds = mergeDocIds;
		}
	}


	map<size_t, set<size_t> >::iterator outIterator;
	for(outIterator = outMap.begin(); outIterator != outMap.end(); outIterator++){
		string outContent;
		sprintf (temp, "%d", outIterator->first);
		outContent.append(temp);
		outContent.append(",");

		size_t i=0;
		set<size_t> outPostingList = outIterator->second;

		for(set<size_t>::iterator it=outPostingList.begin(); it!=outPostingList.end(); ++it){
			sprintf (temp, "%d", *it);
			outContent.append(temp);

			if(i++ < outPostingList.size()-1)
				outContent.append(":");
		}

		outContent.append("\n");
		finalIndexFile << outContent;
	}
	finalIndexFile.close();
	outMap.clear();
}
