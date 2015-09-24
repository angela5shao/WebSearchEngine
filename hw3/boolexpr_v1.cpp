#include "stackint.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
	ifstream boolExpr(argv[1]);
	if (boolExpr.fail()) cout << "File cannot be opened" << endl;

	ifstream var(argv[2]);
	if (var.fail()) cout << "File cannot be opened" << endl;

	// assign values to variables using a map
	map<long unsigned int, bool> varAssign;
	string buf;
	while (getline(var, buf)) {
		istringstream iss(buf);
		int num;
		iss >> num;
		bool numVal;
		char boolVal;
		iss >> boolVal;
		if (boolVal == 'T') numVal = true;
		else numVal = false;
		varAssign.insert(pair<int, bool>(num, numVal));
		cout << "num: " << num << " val: " << numVal << endl;
	}
	

	// read in bool expressions and determine output (4 possible)
	string expr;
	StackInt mystack;
	while (getline(boolExpr, expr)) {
		cout << expr << endl;
		//int len = expr.length();
/*
		istringstream iss(expr);
		while (iss >> ) {
			// if operator or open parenthesis
			// else if a number
			// else a closing parenthesis

			if (expr[i] != ')' && expr[i] != '&' && expr[i] != '|' && expr[i] != '~') { 
				map<int, bool>::iterator it = varAssign.find(expr[i]);

				if (it != varAssign.end()) { // if variable is found, convert to bool & push
					bool boolToPush = it->second;
					mystack.push(boolToPush);
				} else { // else, return "Unknown var" and end program
					cout << "Unknown Variable" << endl;
					return 0;
				}			
			} else if (expr[i] != '(') {
				mystack.push(expr[i]);
			} else {
				bool bool1, bool2;
				char op;

				while (mystack.top() != '(') { // read until we reach '('
					// if read not, not the last popped boolean
					if (mystack.top() == '~') {

					}
				}
				bool1 = mystack.top();
				mystack.pop();
				char op = mystack.top();
				mystack.pop();
				bool2 = mystack.top();
				mystack.pop();
				// check operator
				bool boolRepush;
				if (op == '&') boolRepush = bool1 & bool2;
				else if (op == '|') boolRepush = bool1 | bool2;
				else boolRepush = bool1 
			}

			// if reach end of string and stack isn't empty, return Malformed

		} */
	}


	return 0;
}