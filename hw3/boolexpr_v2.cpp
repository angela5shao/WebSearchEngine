
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
		//cout << "num: " << num << " val: " << numVal << endl;
	}
	

	// declare variables
	string expr;
	StackInt mystack;
	const int OPEN_PAREN = -1;
	const int AND = -2;
	const int OR = -3; 
	const int NOT = -4;
	const int T = -100;
	const int F = -200;

	// read in bool expressions and determine output (4 possible)
	while (getline(boolExpr, expr)) {
		cout << expr << endl;

		int len = expr.length();
		string num = "";
		bool prevWasNum = false;

		for (int i=0; i<len; i++) {
			char c = expr[i];
			long unsigned int y = (long unsigned int) c;
			map<long unsigned int, bool>::iterator it = varAssign.find(y);

			// if numbers
			if (c >= '0' && c <= '9') {
				if (prevWasNum) { // see if need to concatenate
					num += c;
					cout << "  concatenating a num: " << num << endl;
					mystack.pop(); // pop unfinished int
				} else { // new num
					num = c;
					cout << "  new num: " << num << endl;
					prevWasNum = true;
				}
			}

			// if open parenthesis or operators, push
			else if (c == '(' || c == '&' || c == '|' || c == '~') {
				// if last popped was a num, push it
				if (prevWasNum) {
					// push bool-number
					if (it != varAssign.end()) { // if variable is found, convert to bool & push
						cout << "  PUSH a bool-number" << endl;
						if (it->second == 'T') mystack.push(T);
						else mystack.push(F);
					} else { // else, return "Unknown var" and end program
						cout << "  ( and op: Unknown Variable" << endl;
						break;
					}
				}

				prevWasNum = false;
				num = "";

				cout << " PUSH paren or operator" << endl;
				if (c=='(') {
					mystack.push(OPEN_PAREN);
				} else if (c=='&') {
					mystack.push(AND);
				} else if (c=='|') {
					mystack.push(OR);
				} else {
					mystack.push(NOT);
				}
			}

			// else closing parenthesis
			else if (c == ')') {
				// if last popped was a num, push it
				if (prevWasNum) {
					// push bool-number
					if (it != varAssign.end()) { // if variable is found, convert to bool & push
						cout << "  PUSH a bool-number" << endl;
						if (it->second == 'T') mystack.push(T);
						else mystack.push(F);
					} else { // else, return "Unknown var" and end program
						cout << "  ): Unknown Variable" << endl;
						break;
					}
				}
				prevWasNum = false;

				// pop until '(' inclusive
				int fromStack1;
				int op;
				bool gotOp = false;
				while (mystack.top() != OPEN_PAREN) {
					// if stack is empty, Malformed
					if (mystack.empty()) {
						cout << "  Malformed (no matching open paren)" << endl;
						break;
					}
					// if NOT
					else if (mystack.top() == NOT) {
						mystack.pop(); // pop NOT
						// invert last popped bool-number
						cout << "  PUSH inverted bool-number" << endl;
						if (fromStack1 == T) { 
							mystack.push(F);
						}
						else { 
							mystack.push(T);
						}
						gotOp = false;
					// else if a bool-number
					} else if (mystack.top() >= 0) { 
						// if there's an operator, calculate 
						if (gotOp) {
							// find bool equivalent to bool-num
							bool result;
							bool val1, val2;
							if (fromStack1 == T) {
								val1 = true;
							} else val1 = false;
							if (mystack.top() == T) {
								val2 = true;
							} else val2 = false;

							// calculate
							if (op == '&') result = val1 & val2;
							else result = val1 | val2;

							// pop the bool-num and push the newly calculated 
							mystack.pop();
							cout << "  PUSH calculated bool-num" << endl;
							if (result == true) mystack.push(T);
							else mystack.push(F);

						} else { // else, save it and pop
							fromStack1 = mystack.top(); // get the top bool-number
							mystack.pop();
						}
						gotOp = false;
					// else an operator
					} else { 
						// if second/third operator within () isn't same, return Malformed
						if (gotOp && mystack.top() != op) {
							cout << "  Malformed: diff operators" << endl;
							break; // break??????????
						}

						gotOp = true;
						op = mystack.top();
						mystack.pop();
						// depending on operator, 
					}
				}
				mystack.pop(); // pop open parenthesis
			// else blank space
			} else {
				// if last popped was a num, push it
				if (prevWasNum) {
					// push bool-number
					if (it != varAssign.end()) { // if variable is found, convert to bool & push
						cout << "  PUSH a bool-number" << endl;
						if (it->second == 'T') mystack.push(T);
						else mystack.push(F);
					} else { // else, return "Unknown var" and end program
						cout << "  (blank) Unknown Variable" << endl;
						break;
					}
				}
			}
		}
	}

	cout << "mystack: " << endl;
	while (!mystack.empty()) {
		cout << mystack.top() << endl;
		mystack.pop();
	}


	return 0;
}