#include "pageparserMD.h"
#include <iostream>
#include <fstream> 
using namespace std;

void PageParserMD::parse(std::string filename, MySetString& allWords,
		     MySetString& allLinks) {
	// read in all words in file
	ifstream inFile(filename.c_str());
	string word;
	while (inFile >> word) {
		//cout << "word: " << word << "  ";
		int len = word.length();
    	for (unsigned int i=0; i<word.length(); i++) word[i] = tolower(word[i]);
		int begIndex = 0; // index of start of a string
		int begLink = 0;

		// if a link (word[0] == '[')
		if (word[0] == '[') {
			for (int i=0; i<len; i++) {
				if (word[i] == ']') { // if ']' insert text
					// PARSE ANCHOR TEXT
					string anchor_text = word.substr(1, i-1);
					int intermIndex = 0;
					for (unsigned int n=0; n<anchor_text.length(); n++) {
						if ((word[i] >= '0' && word[i] <= '9') ||
							(word[i] >= 'A' && word[i] <= 'Z') || 
							(word[i] >= 'a' && word[i] <= 'z') ) {
							if (i == len-1) 
								allWords.insert(word.substr(intermIndex, len));
						} else { 
							if (i-begIndex != 0) {
								allWords.insert(word.substr(begIndex, i-begIndex));
								intermIndex = i+1;
							}
						}
					}
					allWords.insert(anchor_text); // from index 1, of length 1
					begLink = i+1;
				} else if (word[i] == ')') { // if ')' insert link content
					allLinks.insert(word.substr(begLink+1, i-begLink-1));
					if (i != len-1)
						begIndex = i+1;
				}
			}
		} 
		// else a word (not a link)
		int intermIndex = begIndex;
		for (int i=begIndex; i<len; i++) {
			// if a letter or number, do nothing (pass it)
			if ((word[i] >= '0' && word[i] <= '9') ||
				(word[i] >= 'A' && word[i] <= 'Z') || 
				(word[i] >= 'a' && word[i] <= 'z') ) {
				// if at end of string, insert
				if (i == len-1) {
					//cout << "  insert1: " << word.substr(intermIndex, len) << endl;
					allWords.insert(word.substr(intermIndex, len));
				}
			} else { // else, parse
				// insert only if length != 0
				if (i-begIndex != 0) {
					//cout << "  insert2: " << word.substr(begIndex, i-begIndex) << endl;
					allWords.insert(word.substr(begIndex, i-begIndex));
					intermIndex = i+1;
				}
			}
		}
	} // end of file of words
}