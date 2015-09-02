/* Problem 6 
*/

#include <iostream>
#include <fstream>
using namespace std;

// parses string of non () and [] characters 
void parser(ofstream outfile, string str) {
	//if (str == "")  // base case: if empty str, return
		//return;

	int len = str.length();
	for (int i=0; i<len; i++) {
		// if char isn't letter, output string up to this char, and process string after this char
		if (i == len-1) // if last character
			str >> outfile;
		else if (str[i] < 'a' || str[i] > 'z') {
			str.substr(0,i) >> outfile;
			parser(outfile, str.substr(i+1,len));
		}
	}
}

int main(int argc, char* argv[]) {
	// read name of file 
	ifstream input(argv[1]);
	if (input.fail()) // if file fails
		cout << "File cannot be opened" << endl;

	ofstream output; // create output file

	// read in inputs
	string buf;
	while (input >> buf) {
		// process/parse string
		int len = buf.length();
/*
		for (int i=0; i<len; i++) {
			// if ( found
			if (buf[0] == '(') {
				// find )
				for (int j=1; j<len; j++) {
					// if empty link, output empty string
					if (buf[j] == ')')
				}
				// if ) isn't last character, output whatever is after separately
			}
			else if (buf[0] == '[') {  // else if [ found
				// find ]
			} 
			else if (buf[0] < 'a' || buf[0] > 'z') { // else if not letter
				// skip the letter and output whatever is after separately
			} 
			else {
				// output
			}
		}
*/

	}



	// output into a file (only letters, (), and [])

	// for links: if missing text or link, output empty string

}