#include "webpage.h"
#include "pageparserMD.h"
#include <fstream>
#include <iostream>
using namespace std;


WebPage::WebPage() {}

WebPage::~WebPage() {
	set<WebPage*>::iterator it;
	for (it = outWebSet_.begin(); it != outWebSet_.end(); ++it) 
		delete *it;
	for (it = inWebSet_.begin(); it != inWebSet_.end(); ++it) 
		delete *it;
}

WebPage::WebPage(std::string filename) {
	fname_ = filename;
}

void WebPage::filename(std::string fname) {
	this->fname_ = fname;
}

std::string WebPage::filename() const {
	return fname_;
}

void WebPage::all_words(const myset<string>& words) {
	this->wordSet_ = words;
}

myset<string> WebPage::all_words() const {
	return wordSet_;
}

void WebPage::add_incoming_link(WebPage* wp) {
	inWebSet_.insert(wp);
}

myset<WebPage*> WebPage::incoming_links() const {
	return inWebSet_;
}

myset<string> WebPage::incomingLinkNames() const {
	return inLinkNames_;
}
void WebPage::setIncomingLinkNames(myset<string> set) {
	inLinkNames_ = set;
}

void WebPage::add_outgoing_link(WebPage* wp) {
	outWebSet_.insert(wp);
}

myset<WebPage*> WebPage::outgoing_links() const {
	return outWebSet_;
}

myset<string> WebPage::outgoingLinkNames() const {
	return outLinkNames_;
}
void WebPage::setOutgoingLinkNames(myset<string> set) {
	outLinkNames_ = set;
}

void WebPage::setPR(double pr) {
	pr_ = pr;
}
double WebPage::PR() const {
	return pr_;
}

std::ostream & operator<< (std::ostream & o, const WebPage & page) {
	ifstream file(page.fname_.c_str());
	if (file.fail()) cout << "File cannot be opened" << endl;

	string word;
	while (file >> word) {
		int len = word.length();
		int openParen = 0;

		// if a link 
		if (word[0] == '[') {
			for (int i=0; i<len; i++) {
				if (word[i] == '(') openParen = i;
				if (word[i] == ')') {
					o << word.substr(0, openParen) + word.substr(i+1, len-i-1) << " ";
					break;
				}
			}
		} 
		// else a word (not a link)
		else o << word << " ";
	}
	return o;
}
