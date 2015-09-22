#include "stackint.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	ifstream boolExpr(argv[1]);
	if (boolExpr.fail()) cout << "File cannot be opened" << endl;

	ifstream var(argv[1]);
	if (var.fail()) cout << "File cannot be opened" << endl;



	return 0;
}