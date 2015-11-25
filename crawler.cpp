#include "pageparserMD.h"
#include "webpage.h"
#include "myset.h"
#include "openConfig.h"

#include <set>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void search(string filename, ofstream& o, set<string>& knownFiles); 
void parse(std::string filename, vector<string>& allLinks);

/* Using given seed list, parse each page and evaluate all outgoing links, 
	following the ones not yet known, and continue from those,
	adding working new pages to its index list 
*/
int main(int argc, char* argv[]) {
	char* config;
	if (argc == 1) {
		config = "configCrawler.txt";
	} else {
		config = argv[1];
	}

	openConfig oc(config);
  	map<string, string> configMap = oc.returnMap();

  	ofstream outFile;
  	outFile.open(configMap.find("OUTPUT_FILE")->second.c_str());

	// set to store all pages known
	set<string> knownFiles;

	// open seed list
	ifstream seedFile(configMap.find("INDEX_FILE")->second.c_str());
	if (seedFile.fail()) cout << configMap.find("INDEX_FILE")->second << " not found" << endl;

	// for each file in seed list, call search
	string filename;
	while (seedFile >> filename) {
		search(filename, outFile, knownFiles);
	}

	outFile.close();

	return 0;
}

void search(string filename, ofstream& o, set<string>& knownFiles) {
	// if file of filename exists
	ifstream file(filename.c_str());
	if (file) {
		// if not yet known, add to knownFiles + o
		if (knownFiles.find(filename) == knownFiles.end()) {
			cout << filename << endl;
			knownFiles.insert(filename);
			o << filename << "\n";
		} else { // if known already, pass it
			return;
		}
	} else {
		//cout << filename << " cannot be opened" << endl;
		return;
	}
		

	// parse the file
	vector<string> outlinks;
	parse(filename, outlinks);


	// if outlinks is empty (file is a leaf), return
	if (outlinks.size() == 0) {
		return;
	} else {
		// for each outlink
		for (vector<string>::iterator it = outlinks.begin(); it != outlinks.end(); ++it) {
			// search the outgoing link
			search(*it, o, knownFiles);
		}
	}
}

void parse(std::string filename, vector<string>& allLinks) {
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
			} else {
				// if '(' store index
				if (word[h] == '(') {
					openP = h;
					insideBorP = true;
				}
				// if ')' add to allLinks, update t
				else if (word[h] == ')') {
					allLinks.push_back(word.substr(openP + 1, h-openP-1));
					//cout << "add link: " << word.substr(openP + 1, h-openP-1) << endl;
					//cout << "    @ ), h=" << h << " t=" << t << endl;
					t = h+1;
					insideBorP = false;
				}
			}
			h++;
		}
	}

}