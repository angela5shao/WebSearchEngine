#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

void addToEnds(string str, int len);
void makePalindromes(ostream& ofile, char* options, int size);

int main(int argc, char* argv[])
{
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

void addToEnds(string str, string bank, int size) {
	cout << "addToEnds..." << endl;
	int len = str.length();
	string buf = "";

	if (len <= size-2) {
		// for each char in str, add to both ends of str
		for (int i=0; i<size; i++) {
			buf = bank[i] + str + bank[i];
			cout << buf << endl;
			//addToEnds(buf, size);
		}
	}
	else return;

}

void makePalindromes(ostream& ofile, char* options, int size) {
	string bank(options);
	int len = bank.length();
	
	for (int i=0; i<len; i++) {
		cout << "for " << bank[i] << "..." << endl;
		string str = "" + bank[i];
		cout << "str:" << str << endl; /*
		// add a char of each char to both ends of bank[i]
		for (int j=0; j<len; j++) {
			addToEnds(str, bank, len);
		}*/

	}


	// for each char in bank (which is itself a palindrome)
	for (int i=0; i<len; i++) {
/*
		// output string of this char with len/2
		string buf = " " + bank[i];
		cout << "char: " << bank[i] << endl;
		cout << "buf: " << buf << endl;
		for (int l=0; l<len/2; l++) {
			buf = buf + bank[i];
			cout << buf << endl;
			// for each of these same-char string: add char in bank to both ends until len=size

		}*/

/*
		string buf = "";
		// repeat itself of length 1 to (len-1)
		for (int j=0; j<len; j++) {
			buf = buf + bank[i];
			// for each string of repeated 

			cout << buf << endl;
		}
		*/
	}
	// ** remember empty string **
}