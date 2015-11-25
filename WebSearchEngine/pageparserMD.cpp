#include "pageparserMD.h"
#include <iostream>
#include <fstream> 
using namespace std;


// to parse anchor text (word may have space and special characters)
void PageParserMD::parseHelper(string word, myset<string>& allWords) {
	int start = 0;
	for (unsigned int i=0; i<word.length(); i++) {
		// if a letter or number, do nothing (pass it)
		if ((word[i] >= '0' && word[i] <= '9') ||
			(word[i] >= 'A' && word[i] <= 'Z') || 
			(word[i] >= 'a' && word[i] <= 'z') ) {

			// if at end of string, add word
			if (i == word.length()-1) {
				allWords.insert(word.substr(start, word.length()-start));
				//cout << "add Aword: " << word.substr(start, word.length()-start) << endl;
			}
		} else { // else, parse
			allWords.insert(word.substr(start, i-start));
			//cout << "add Aword: " << word.substr(start, i-start) << endl;
			start = i+1;
		}
	}
}

void PageParserMD::parse(std::string filename, myset<string>& allWords,
		     myset<string>& allLinks) {
	// read in all words in file
	ifstream inFile(filename.c_str());
	if (!inFile) cout << filename << " cannot be opened" << endl;
	string word;

while (getline(inFile, word)) {
	//getline(inFile, word); 
	int len = word.length();
	for (unsigned int i=0; i<word.length(); i++) word[i] = tolower(word[i]);

	// initiate tail (stays until add word/link) and head (always moves) indices
	int h=0, t=0;
	// index for open parenthesis and bracket
	int openB = 0, openP = 0;
	bool insideBorP = false;

	while (h < len) {
		// if a letter or number, do nothing
		if ((word[h] >= '0' && word[h] <= '9') ||
			(word[h] >= 'A' && word[h] <= 'Z') || 
			(word[h] >= 'a' && word[h] <= 'z') ) {
			// but if at end of word, add to allWords
			if (h == len-1) {
				allWords.insert(word.substr(t, h-t));
			}

		} else {
			// if it's '[', store index
			if (word[h] == '[') {
				openB = h;
				insideBorP = true;
			} 
			// if ']', parse anchor text by calling helper, update t
			else if (word[h] == ']') {
				parseHelper(word.substr(openB+1, h-openB-1), allWords);
				//cout << "    @ ], h=" << h << " t=" << t << endl;
				t = h+1;
				insideBorP = false;
			}
			// if '(' store index
			else if (word[h] == '(') {
				openP = h;
				insideBorP = true;
			}
			// if ')' add to allLinks
			else if (word[h] == ')') {
				// only add the link if a valid link with anchor text
				if (word[openP-1] == ']') {
					allLinks.insert(word.substr(openP + 1, h-openP-1));
					t = h+1;
				}
				insideBorP = false;
			}
			// else, parse everything h->t & update t
			else {
				// if the next char is a blank, add if there's something before word[h]
				// if next char is a special char, update 	
				if (word[h+1] == ' ') {
				/*if ((word[h+1] < '0' || word[h+1] > '9') &&
					(word[h+1] < 'A' || word[h+1] > 'Z') && 
					(word[h+1] < 'a' || word[h+1] > 'z') ) { */
					if (word.substr(t, h-t).size() != 0) {
						allWords.insert(word.substr(t, h-t));
						//cout << "add word1 @ " << word[h] << ": " << word.substr(t, h-t) << endl;
					}
					h++;
					t = h+1;
				}
				// if not inside paren or bracket
				else if (!insideBorP) {
					if (word.substr(t, h-t).size() != 0) {
						allWords.insert(word.substr(t, h-t));
						//cout << "add word @ " << word[h] << ": " << word.substr(t, h-t) << endl;
					//cout << "    @ spc, h=" << h << " t=" << t << endl;
					}
					t = h+1;
				}
			}
		}
		h++;
	}
}

}