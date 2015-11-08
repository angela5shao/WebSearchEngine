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
}

void SearchEng::add_parse_from_index_file(std::string index_file, PageParser* parser) {
	ifstream indexF(index_file.c_str());
	if (indexF.fail()) cout << "Cannot open index file" << endl;

	string file;
	while(indexF >> file) { // for each file, call add_parse_page
		this->add_parse_page(file, parser);
	}

	map<string, MySetString>::iterator it;
	// for each file in outLink_ map
	for (it = outLink_.begin(); it != outLink_.end(); ++it) {
		// find its web
		WebPage* page = fileMap_.find(it->first)->second;
		MySetString outS = it->second;
		for (set<string>::iterator it2 = outS.begin(); it2 != outS.end(); ++it2) {
			WebPage* outPg = fileMap_.find(*it2)->second; 
			page->add_outgoing_link(outPg);
			outPg->add_incoming_link(page);
		}
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
	set<string>::iterator itS;
	for (itS = parsedWordSet.begin(); itS != parsedWordSet.end(); ++itS) {
		string buf = *itS;
		for (int i=0; i<buf.length(); i++) {
			buf[i] = tolower(buf[i]);
		}
	}
	outLink_.insert(pair<string, MySetString>(filename, outLinkSet));

	// if current page doesn't already exists
	allPages_.insert(page);
	fileMap_.insert(pair<string, WebPage*>(filename, page));
	

	// for each word in parsedWordSet
	set<string>::iterator it1;
	for (it1 = parsedWordSet.begin(); it1 != parsedWordSet.end(); ++it1) {
		if (myMap_.find(*it1) != myMap_.end()) { // if already in map, add this page's addr
			//myMap_.find(*it1)->second.push_back(page);
			myMap_.find(*it1)->second.push_back(fileMap_.find(page->filename())->second);
		} else { // else add the word/page-addr pair to map
			vector<WebPage*> v1;
			//v1.push_back(page);
			v1.push_back(fileMap_.find(page->filename())->second);
			myMap_.insert(pair<string, vector<WebPage*> >(*it1, v1));
		}
	}

	delete parser;
	parser = NULL;
}

MySetWebPage SearchEng::findPg(string words) {
	MySetWebPage resultSet;
	vector<WebPage*>::iterator it;

	if (myMap_.find(words) != myMap_.end()) {
		for (it = myMap_.find(words)->second.begin(); it != myMap_.find(words)->second.end(); ++it) {
			resultSet.insert(*it);
		}
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

WebPage* SearchEng::findWebPage(std::string filename) {
	return fileMap_.find(filename)->second;
}