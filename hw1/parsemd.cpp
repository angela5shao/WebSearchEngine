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
	//if (str == "") return; // base case

	for (int i=0; i<len; i++) {
		// if any char isn't a letter, print out whatever is before it and call parser for what's after
		if (str[i] < 'a' || str[i] > 'z') {
			cout << str.substr(0,i) << endl;
			//parser(str.substr(i+1,len));
		}
	}
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

		// if starts with '(' or '[', output what's inside
		if (buf[0] == '(' || buf[0] == '[') {
			// if something is after ')' or ']', output what's inside
			for (int i=0; i<len; i++) {
				if (buf[i] == ')' || buf[i] == ']') {
					cout << buf.substr(1,i) << endl;
				}
			}
		}

		// else: check for non-letters
		else {
			// if reach non-letter, print what's before
			for (int i=0; i<len; i++) {
				if (buf[i] < 'a' || buf[i] > 'z') { // ** CHECK FOR CAPITALS TOO ** */
					cout << buf.substr(0,i) << endl;
				}
			}
		}

	}
}