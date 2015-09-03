/* Problem 6 */

#include <iostream>
#include <fstream>
using namespace std;

/* Purpose: Takes in string, parse out non-letters, return words
Param: string 
Output: string
*/
void parser(string str, ofstream &output) {
	int len = str.length();

	if (str == "") return; // base case

	for (int i=0; i<len; i++) {
		// if a special char, print what's before and call parser for what's after
		char x = str[i];
		if (x < 'A' || (x > 'Z' && x < 'a') || x > 'z') {
			// if not first character
			if (i != 0) {
				cout << str.substr(0,i) << endl;
				output << str.substr(0,i) << endl;
			}
			parser(str.substr(i+1, len), output);
			break;
		}
		// if entire string are letters
		if (i==len-1) {
			cout << str << /*" (normal)" << */endl;
			output << str << endl;
		}
	}
}

/* process links without anchor text; PRINTS
Param: string, including ()
Output: LINK (content, content)
 */
void outputLink(string str, ofstream &output) {
	int len = str.length();
	// find ')' and output
	for (int i=1; i<len; i++) {
		if (str[i] == ')') {
			string buf = str.substr(1,i-1);
			cout << "LINK (" << buf << ", " << buf << ")";

			string temp = "LINK (" + buf + " " + buf + ")";
			output << temp << endl;

			// if ')' isn't end of str, call parser for what's after ')'
			if (i != len-1) {
				parser(str.substr(i+1,len), output);
			}
		}
	}
}

/* process links with anchor text; PRINTS
Param: string, including [] and ()
Output: LINK (content, anchor_text)
*/
void outputLinkWithAnchor(string str, ofstream &output) {
	int len = str.length();
	string anchor;
	int indexOpenParen;
	
	for (int i=1; i<len; i++) {
		// find ']' and see if '(' follows
		if (str[i] == ']') {
			// if followed by '(' with a link, save anchorText
			if (str[i+1] == '(') {
				anchor = str.substr(1,i-1);
				indexOpenParen = i+1;
			}
			// else, print content
			else {
				cout << /*" (no link) " <<*/ str.substr(1,i-1) << endl;
				output << str.substr(1,i-1) << endl;
				break;
			}
		}
		// find ')'
		if (str[i] == ')') {
			string buf = str.substr(indexOpenParen + 1, i);
			cout << "LINK (" << buf << ", " << anchor << ")" << endl;

			string temp = "LINK (" + buf + ", " + anchor + ")";
			output << temp << endl;

			// if ')' isn't end of str, call parser for what's after ')'
			if (i != len-1) {
				parser(str.substr(i+1,len), output);
			}
		}
	}
}

int main(int argc, char* argv[]) {
	// read file 
	ifstream input(argv[1]);
	if (input.fail()) // if file fails
		cout << "File cannot be opened" << endl;

	ofstream output; // create output file and open it
	output.open(argv[2]);

	// read in inputs
	string buf;
	while (input >> buf) {
		//cout << buf << endl;

		if (buf[0] == '(') { // if starts with '(', call outputLink
			outputLink(buf, output);
		} else if (buf[0] == '[') { // else if starts with '[', call outputLinkWithAnchor
			outputLinkWithAnchor(buf, output);
		} else { // else, call parser
			parser(buf, output);
		}
	}

	// close output file
	output.close();

	return 0;
}