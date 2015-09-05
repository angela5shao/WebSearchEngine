#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

void addToEnds(ofstream &ofile, string temp, string orig, int size);
void makePalindromes(ofstream& ofile, char* options, int size);

int main(int argc, char* argv[]) {
  if(argc < 4){
    cerr << "Please provide an output file, a string of characters, and the max length" << endl;
    return 1;
  }

  ofstream ofile(argv[1]);
  int len = atoi(argv[3]);
  makePalindromes(ofile, argv[2], len);
  ofile.close();
  return 0;
}

void addToEnds(ofstream& ofile, string temp, string orig, int size) {
	int len = temp.length();
	int lenOrig = orig.length();
	string buf = "";

	if (len <= size-2) {
		// for each char in str, add to both ends of str
		for (int i=0; i<lenOrig; i++) {
			buf = orig[i] + temp + orig[i];
			ofile << buf << endl;

			addToEnds(ofile, buf, orig, size);
		}
	}
	else return;
}

void makePalindromes(ofstream& ofile, char* options, int size) {
	string orig(options);
	int len = orig.length();

	if (len == 0) {
		ofile << orig << endl;
	}
	else {
		// for each char in orig
		for (int i=0; i<len; i++) {
			// for strings of odd length
			string temp1 = "";
			ofile << temp1 << endl;
			temp1 = temp1 + orig[i];
			ofile << temp1 << endl;
			addToEnds(ofile, temp1, orig, size);

			// for strings of even length
			string temp2 = "";
			temp2 = orig[i] + temp2 + orig[i];
			ofile << temp2 << endl;
			addToEnds(ofile, temp2, orig, size);
		}
	}
}