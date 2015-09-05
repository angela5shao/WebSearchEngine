#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	string s1 = "abcde";
	for (int i=0; i<s1.length(); i++) {
		string temp = "";
		cout << temp  + s1[i] <<endl;

		string temp2 = "";
		temp2 = temp2 + s1[i];
		cout << temp2 << endl;
	}

	return 0;
}