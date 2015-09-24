// valgrind --leak-check=full --show-leak-kinds=all -v ./boolexpr
#include "stackint.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string> // for atoi
#include <cstdlib>
#include <vector>
using namespace std;

bool toBool(int x) {
	if (x == -10) return true;
	else return false;
}

int main(int argc, char* argv[]) {
	ifstream boolExpr(argv[1]);
	if (boolExpr.fail()) cout << "File cannot be opened" << endl;

	ifstream var(argv[2]);
	if (var.fail()) cout << "File cannot be opened" << endl;

	// assign values to variables using a map
	map<long int, bool> varAssign;
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
	const int T = -10;
	const int F = -20;

	// read in and process expressions
	while (getline(boolExpr, expr)) {
		cout << expr << endl;
		int len = expr.length();

		int b1;
		int op;
		bool hasB1 = false;
		bool hasOp = false;
		bool hasResult = false;

		for (int i=0; i<len; i++) {
			char c = expr[i];

			// if numbers
			if (c >= '0' && c <= '9') {
				// get whole number (until char isn't a number)
				string num = "";
				num += c;
				while (expr[i+1] >= '0' && expr[i+1] <= '9') {
					num += expr[i+1];
					i++;
				}
				
				long int x = atoi(num.c_str());	
				map<long int, bool>::iterator it;
				it = varAssign.find(x);
				if (it != varAssign.end()) {
					//cout << "  number:" << it->first << " val:" << it->second << endl;
					int toPush;
					if (it->second) toPush = T;
					else toPush = F;
					mystack.push(toPush);
				}
			}

			// if open parenthesis or operators, push
			else if (c == '(' || c == '&' || c == '|' || c == '~') {
				if (c=='(') {
					//cout << "  push: " << OPEN_PAREN << endl;
					mystack.push(OPEN_PAREN);
				} else if (c=='&') {
					//cout << "  push: " << AND << endl;
					mystack.push(AND);
				} else if (c=='|') {
					mystack.push(OR);
				} else { // not
					// retrieve last bool-number
					int x = mystack.top();
					mystack.pop();

					if (x == T) { // pop from vector and add inverse
						mystack.push(F);
					} else { 
						mystack.push(T);
					}
				}
			}

			// else closing parenthesis, CALCULATE!
			else if (c == ')') {
				cout << "  .. reached ) and top=" << mystack.top() << endl;
				
				while (1) {
					if (mystack.top() == OPEN_PAREN) {
						cout << "  .. reached (  ";
						break;
					}
					if (mystack.empty()) { // if no corresponding '('
						cout << "Malformed: no matching (" << endl;
						break;
					}

					int x = mystack.top(); // which is after '('
					cout << "  .. pop " << x;
					/*if (!hasResult) */mystack.pop();

					if (x == T || x == F) {
						if (hasB1 && hasOp) { // if hasB1, calculate and push on vector
							if ((toBool(x) && toBool(b1)) || (toBool(x) || toBool(b1))) {
								mystack.push(T);
								cout << "  .. push ANS: T (==" << mystack.top() <<")" << endl;
							} else { 
								mystack.push(F);
								cout << "  .. push ANS: F (==" << mystack.top() <<")" << endl;
							}
							hasResult = true; 
							//cout << "  .. hasResult==1? " << hasResult << endl;
							hasB1 = false;

							// don't pop this result!!!!

						} else if (hasB1 && !hasOp) { // hasB1 but !hasOp
							cout << "Malformed: 2 num w/o operator" << endl;
							break;
						} else { // hasB1
							cout << "  setting b1" << endl;
							b1 = x;
							hasB1 = true;
						}
					} else if (x == AND) { // an AND
						if (hasOp && op != AND) {
							cout << "Malformed: inconsistent operator" << endl;
							break;
						} else if (!hasB1) {
							cout << "Malformed: op without a variable" << endl;
							break;
						}
						cout << "  setting op = AND" << endl;
						op = AND;
						hasOp = true;
					} else if (x == OR) { // an OR
						if (hasOp && op != OR) {
							cout << "Malformed: inconsistent operator" << endl;
							break;
						} else if (!hasB1) {
							cout << "Malformed: op without a variable" << endl;
							break;
						}
						cout << "  setting op = OR" << endl;
						op = OR;
						hasOp = true;
					} else {
						cout << "  unrecognized int in miniExpr" << endl;
						break;
					}
				} // end of mini expression 

				cout << "  .. popped " << mystack.top() << ", which should be -1" << endl;
				mystack.pop(); // pop '('
				
				hasOp = false; 
				hasB1 = false;
			} 
			
			else {// else blank space or end of expression
				// if what's left is '('
			}
			
		} // finish pushing entire expression
		
		int result = mystack.top();
		mystack.pop();
		if (result == T) cout << "TRUE" << endl;
		else cout << "FALSE" << endl;

		if (!mystack.empty()) { // if stack isn't empty, output Malformed
			cout << "Malformed: something left still" << endl;
		}

	} // end of while loop (input file)

	return 0;
}