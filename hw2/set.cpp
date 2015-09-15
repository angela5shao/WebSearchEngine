/* Problem 7: using STL set, read text file, 
let user query if certain words are in the file */

#include <iostream>
#include <fstream>
#include <set>
#include <string> // for converting to lower case
using namespace std;

/* parses when non-letters are reached
param: input string, set (to insert)
return: none
*/
void parse(string input, set<string> &myset) {
	// BASE: input is empty
	if (input.empty()) return;

	int lenInput = input.length();
	// loop thru each char in input
	for (int i=0; i<lenInput; i++) {
		input[i] = tolower(input[i]); // convert input to lowercase
		// when non-letter reached, input what's before into set
		if (input[i] < 'A' || (input[i] > 'Z' && input[i] < 'a') || input[i] > 'z') {
			myset.insert(input.substr(0,i));
			parse(input.substr(i+1, lenInput), myset);
			return;
		} 
	}
	myset.insert(input);
}

int main(int argc, char* argv[]) {
	// read in file
	ifstream input(argv[1]);
	if (input.fail()) // if file fails
		cout << "File cannot be opened" << endl;

	// create a set
	set<string> myset;
	string buf = "";
	while (input >> buf) {
		parse(buf, myset);
	}

	// query input & parse
	string userIn = "";
	while (getline(cin, userIn)) {
		// check if user enters "RETURN" key
		if (userIn == "") break;

		// make userIn lowercase
		int len = userIn.length();
		for (int i=0; i<len; i++) {
			userIn[i] = tolower(userIn[i]);
		}

		if (myset.count(userIn) == 1) { // if userIn exists in set
			cout << "in the file" << endl;
		} else {
			cout << "not in file" << endl;
		}
	}
	return 0;
}