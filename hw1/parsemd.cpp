/* Problem 6 */

#include <iostream>
#include <fstream>
using namespace std;

/* Purpose: Takes in string, parse out non-letters, return words
Param: string 
Output: string
*/
void parser(string str) {
	int len = str.length();
	//cout << str << ": ";

	if (str == "") return;

	for (int i=0; i<len; i++) {
		// if a special char, print what's before and call parser for what's after
		char x = str[i];
		
		if (x < 'A' || (x > 'Z' && x < 'a') || x > 'z') {
			cout << str.substr(0,i) << endl;
			parser(str.substr(i+1, len));
			break;
		}
		// if entire string are letters
		if (i==len-1) {
			cout << str << " (normal)" << endl;
		}
	}

	//cout << " (end of parser)" << endl;

/*
	for (int i=0; i<len; i++) {
		// if any char isn't a letter, print out whatever is before it and call parser for what's after
		if (str[i] < 'a' || str[i] > 'z') {
			cout << str.substr(0,i) << endl;
			//parser(str.substr(i+1,len));
		}
	}*/
}

/* process links without anchor text; PRINTS
Param: string, including ()
Output: LINK (content, content)
 */
void outputLink(string str) {
	int len = str.length();
	// find ')' and output
	for (int i=1; i<len; i++) {
		if (str[i] == ')') {
			string buf = str.substr(1,i-1);
			cout << "LINK (" << buf << ", " << buf << ")";
			// if ')' isn't end of str, call parser for what's after ')'
			if (i != len-1) {
				cout << "(calling parser!)" << endl;
				parser(str.substr(i+1,len));
			}
		}
	}
}

/* process links with anchor text; PRINTS
Param: string, including [] and ()
Output: LINK (content, anchor_text)
*/
void outputLinkWithAnchor(string str) {
	// find ']' and see if '(' follows

		// if '(' doesn't follow, output content inside []

		// else, output
}

int main(int argc, char* argv[]) {
	// read file 
	ifstream input(argv[1]);
	if (input.fail()) // if file fails
		cout << "File cannot be opened" << endl;

	ofstream output; // create output file

	// read in inputs
	string buf;
	while (input >> buf) {
		int len = buf.length();
		//cout << buf << endl;

		// if starts with '(', call outputLink
		if (buf[0] == '(') {
			outputLink(buf);
		}

		// else if starts with '[', call outputLinkWithAnchor
/*
		else if (buf[0] == '[') {
			outputLinkWithAnchor(buf);
		}*/
		// else, call parser
		else {
			// if reach non-letter, print what's before
			parser(buf);
		}

	}
}