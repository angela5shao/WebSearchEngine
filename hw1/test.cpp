#include <iostream>
#include <fstream>
using namespace std;

// parses string of non () and [] characters 
void parser(string str) {
	if (str == "") { // base case: if empty str, return
		return;
	}

	int len = str.length();
	for (int i=0; i<len; i++) {
		// if char isn't letter, output string up to this char, and process string after this char
		if (i==len-1) {
			
		}
		else if (str[i] < 'a' || str[i] > 'z') {
			//str.substr(0,i) >> outfile;
			cout << str.substr(0,i) << endl;
			parser(str.substr(i+1,len-1));
		} else if (i == len-1) { // if last char
			//str >> outfile;
			cout << str << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	ifstream input(argv[1]);
	if (input.fail()) // if file fails
		cout << "File cannot be opened" << endl;

	ofstream output; // create output file

	// read in inputs
	string buf;
	/*while (input >> buf) {
		parser(buf);
	}*/
	input >> buf;
	parser(buf);

	return 0;
}