// work on line 104
#include "searcheng.h"
#include "pageparserMD.h"
#include "webpage.h"
#include "myset.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

SearchEng::SearchEng() {
}
SearchEng::~SearchEng() {
	// delete dynamically allocated WebPages in allPages set
	set<WebPage*>::iterator it;
	for (it = allPages_.begin(); it != allPages_.end(); ++it) 
		delete *it;
}

void SearchEng::add_parse_from_index_file(std::string index_file, PageParser* parser) {
	ifstream indexF(index_file.c_str());
	if (indexF.fail()) cout << "Cannot open index file" << endl;

	string file;
	while(indexF >> file) { // for each file, call add_parse_page
		this->add_parse_page(file, parser);
	}
}

void SearchEng::add_parse_page(std::string filename, PageParser* parser) {
	// parse the page's content
	MySetString parsedWordSet;
	parser = new PageParserMD;
	MySetString outLinkSet;
	parser->parse(filename, parsedWordSet, outLinkSet);

	// create a WebPage* for a new page
	WebPage* page = new WebPage;
	page->filename(filename);
	page->all_words(parsedWordSet);

	// add this page to allPages set and fileMap
	allPages_.insert(page);
	fileMap_.insert(pair<string, WebPage*>(filename, page));

	// for each link in outLinkSet (MySetString), find its WebPage* in fileMap_
	set<string>::iterator it;
	for (it = outLinkSet.begin(); it != outLinkSet.end(); ++it) {
		// if filename's WebPage* doesn't exist in fileMap_
		if (fileMap_.find(*it) == fileMap_.end()) {
			WebPage* newPage = new WebPage;
			newPage->filename(*it);
			fileMap_.insert(pair<string, WebPage*>(*it, newPage));
		} 
		// if page already exists in fileMap_, update incoming & outgoing
			WebPage* existedPg = fileMap_.find(*it)->second;
			page->add_outgoing_link(existedPg); // add it to page's outgoing_link
			existedPg->add_incoming_link(page); // add page to its incoming_link
		
	}

	// for each word in parsedWordSet
	for (it = parsedWordSet.begin(); it != parsedWordSet.end(); ++it) {
		
		if (myMap_.find(*it) != myMap_.end()) { // if already in map, add this page's addr
			myMap_.find(*it)->second.push_back(page);
		} else { // else add the word/page-addr pair to map
			vector<WebPage*> v1;
			v1.push_back(page);
			myMap_.insert(pair<string, vector<WebPage*> >(*it, v1));
		}
	}

	delete parser;
	parser = NULL;
}

MySetWebPage SearchEng::findPg(string words) {
	MySetWebPage resultSet;
	vector<WebPage*>::iterator it;

	if (myMap_.find(words) != myMap_.end()) {
		for (it = myMap_.find(words)->second.begin(); it != myMap_.find(words)->second.end(); ++it) 
			resultSet.insert(*it);
	}
	return resultSet;
}

MySetWebPage SearchEng::findANDPg(string words) {
	stringstream iss(words);
	string buf;
	MySetWebPage resultSet;

	// insert pages for first word
	iss >> buf;
	vector<WebPage*>::iterator it; // points to WebPage*
	if (myMap_.find(buf) != myMap_.end()) {
		for (it = myMap_.find(buf)->second.begin(); it != myMap_.find(buf)->second.end(); ++it)
			resultSet.insert(*it);
	}

	while (iss >> buf) { // for each word, save its matching pages
		MySetWebPage tempPgSet;

		if (myMap_.find(buf) != myMap_.end()) {
			for (it = myMap_.find(buf)->second.begin(); it != myMap_.find(buf)->second.end(); ++it) {
				tempPgSet.insert(*it);
			}
		}
		resultSet = resultSet.set_intersection(tempPgSet); // find intersection
	}
	return resultSet;
}

MySetWebPage SearchEng::findORPg(string words) {
	stringstream iss(words);
	string buf;
	MySetWebPage resultSet;

	// insert pages for first word
	iss >> buf;
	vector<WebPage*>::iterator it; // points to WebPage*
	if (myMap_.find(buf) != myMap_.end()) {
		for (it = myMap_.find(buf)->second.begin(); it != myMap_.find(buf)->second.end(); ++it)
			resultSet.insert(*it);
	}

	while (iss >> buf) { // for each word, save its matching pages
		MySetWebPage tempPgSet;

		if (myMap_.find(buf) != myMap_.end()) {
			for (it = myMap_.find(buf)->second.begin(); it != myMap_.find(buf)->second.end(); ++it) 
				tempPgSet.insert(*it);
		}
		resultSet = resultSet.set_union(tempPgSet); // find union
	}
	return resultSet;
}