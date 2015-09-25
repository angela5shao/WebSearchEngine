/* valgrind --leak-check=full --show-leak-kinds=all -v ./boolexpr
 g++ -g -Wall boolexpr.cpp stackint.cpp alistint.cpp -o boolexpr
 ./boolexpr boolexpr.in boolexpr.vars
*/
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

		int b1; // first number
		int op;
		bool hasB1 = false;
		bool hasOp = false;
		// variable for presence of T/F
		bool andHasFalse = false;
		bool orHasTrue = false;

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
					int toPush;
					if (it->second) toPush = T;
					else toPush = F;
					mystack.push(toPush);
					//cout << "  pushed: " << mystack.top() << endl;
				}
			}

			// if open parenthesis or operators, push
			else if (c == '(' || c == '&' || c == '|' || c == '~') {
				if (c=='(') {
					mystack.push(OPEN_PAREN);
				} else if (c=='&') {
					mystack.push(AND);
				} else if (c=='|') {
					mystack.push(OR);
				} else { // not
					mystack.push(NOT);					
				}
				//cout << "  pushed: " << mystack.top() << endl;
			}

			// else closing parenthesis, CALCULATE!
			else if (c == ')') {
				// read until '('
				while (1) {
					int x = mystack.top();
					cout << "  " << x;
					mystack.pop();

					if (x == OPEN_PAREN) {
						cout << "  reached (  ";

						// calculate
						if (op == AND && andHasFalse) {
							mystack.push(F);
							cout << "  AND push F" << endl;
						} else if (op == AND || (op == OR && orHasTrue)) {
							mystack.push(T);
							cout << "  AND/OR push T" << endl;
						} else if (op == OR) {
							mystack.push(F);
							cout << "  OR push F" << endl;
						}
						// TEST
						int x1 = mystack.top();
						mystack.pop();
						int x2 = mystack.top();
						cout << "  at top:" << x1 << " then " << x2 << endl;
						mystack.push(x1);

						// reset
						hasB1 = false;
						hasOp = false;
						andHasFalse = false;
						orHasTrue = false;
						break;

					} else if (mystack.empty()) { // no matching '('
						cout << "  no matching (" << endl;
						break;
					}

					// if number
					if (x == T || x == F) {
						// if hasB1
						if (hasB1) {
							// check if it is NOTed
							int maybeNOT = mystack.top();
							bool isNOT = false;
							if (maybeNOT == NOT) {
								mystack.pop(); // pop NOT
								isNOT = true;
							}

							if (op == AND) { // if op = AND
								if (x == F || (x==T && isNOT)) {
									andHasFalse = true;
								}
							} else if (op == OR) { // else if op = OR
								if (x == T || (x==F && isNOT)) {
									orHasTrue = true;
								}
							} else { // else, no op, malformed (no op for number)
								cout << "  MALFORMED: no op" << endl;
								break;
							}
						} else { // store as b1
							b1 = x;
							hasB1 = true;
						}
					} else if (x == AND) { // if AND
						if (hasOp && op != AND) {
							cout << "  MALFORMED: inconsistent op" << endl;
							break;
						}
						cout << " (op=AND) ";
						op = AND;
						hasOp = true;
						if (b1 == F) andHasFalse = true;

					} else if (x == OR) { // if OR
						if (hasOp && op != OR) {
							cout << "  MALFORMED: inconsistent op" << endl;
							break;
						}
						cout << " (op=OR) ";;
						op = OR;
						hasOp = true;
						if (b1 == T) orHasTrue = true;

					} else if (x == NOT) { // if NOT
						// check if it is NOTed
						int maybeNOT = mystack.top();
						bool isNOT = false;
						if (maybeNOT == NOT) {
							mystack.pop(); // pop NOT
							isNOT = true;
						}

						if (op == AND) { // if op = AND
							if (x == F || (x==T && isNOT)) {
								andHasFalse = true;
							}
						} else if (op == OR) { // else if op = OR
							if (x == T || (x==F && isNOT)) {
								orHasTrue = true;
							}
						}

						/*// grab last int and push its inverse
						int temp = mystack.top();
						cout << "  inversing " << temp << endl;
						mystack.pop();
						if (temp == T) mystack.push(F);
						else mystack.push(T);*/

					} else { // blank or unrecognized, do nothing

					}

				}/*
				
			} 
			
			else {// else blank space or end of expression
				// if what's left is '('
			}
			
		} // finish pushing entire 



/*
		int result = mystack.top();
		mystack.pop();
		if (result == T) cout << "TRUE" << endl;
		else cout << "FALSE" << endl;

		if (!mystack.empty()) { // if stack isn't empty, output Malformed
			cout << "Malformed: " << mystack.top() << " left still" << endl;
		}
*/
	} // end of while loop (input file)
/*
	cout << "STACK:  ";
	while (!mystack.empty()) {
		cout << mystack.top() << " ";
		mystack.pop();
	}
	cout << endl;*/


	return 0;
}