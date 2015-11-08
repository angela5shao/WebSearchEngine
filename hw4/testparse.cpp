#include <iostream>
#include "pageparserMD.h"
#include "myset.h"
using namespace std;

int main(int argc, char* argv[]) {
	//string infile = "Hello world [hi](data2.txt). Table chair desK, t-bone steak.";
	MySetString words;
	MySetString links;

	PageParserMD pageparser; 
	pageparser.parse(argv[1], words, links);


	int wordCnt = 0;
	std::set<std::string>::iterator it;
	cout << "\nWords: ";
	for (it = words.begin(); it != words.end(); ++it) {
		cout << *it << " ";
		wordCnt++;
	}
	cout << " | cnt: " << wordCnt << endl;

	cout << "Links: ";
	for (it = links.begin(); it != links.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}