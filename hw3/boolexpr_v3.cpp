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

	// read in bool expressions and determine output (4 possible)
	while (getline(boolExpr, expr)) {
		cout << expr << endl;
		int len = expr.length();

		for (int i=0; i<len; i++) {
			char c = expr[i];
			map<long int, bool>::iterator it;

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
				//cout << "  int: " << x << endl;

				it = varAssign.find(x);
				if (it != varAssign.end()) {
					//cout << "  number:" << it->first << " val:" << it->second << endl;
					int toPush;
					if (it->second) toPush = T;
					else toPush = F;
					//cout << "  push: " << toPush << endl;
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
				/*cout << "STACK:" << endl;
				while (!mystack.empty()) {
					cout << "  " << mystack.top() << endl;
					mystack.pop();
				}*/
				vector<int> miniExpr;

				// TEST STACK CONTENT
				/*cout << "STACK:";
				while (!mystack.empty()) {
					cout << " " << mystack.top();
					mystack.pop();
				} cout << endl;*/

				// transfer stack to vector (which is in reverse order)
				while (mystack.top() != OPEN_PAREN) {
					/*if (mystack.top() == NOT) { 
						// retrieve last bool-number
						int x = miniExpr.back();
						miniExpr.pop_back();

						if (x == T) { // pop from vector and add inverse
							miniExpr.push_back(F);
						} else { 
							miniExpr.push_back(T);
						}
					} else {
						
					}*/
					miniExpr.push_back(mystack.top());
					mystack.pop(); // pop the last char
					
					if (mystack.empty()) { // if no corresponding '('
						cout << "Malformed: no matching (" << endl;
						break;
					}
				}
				mystack.pop(); // pop '('

				// at this point, guarantees matching () and no ~ but not consistent operator
				vector<int>::iterator it = miniExpr.end();
				int b1;
				bool hasB1 = false;
				bool hasOp = false;
				bool hasResult = false;
				int op;
				int numBuf;

				// TEST: PRINT VECTOR (raw)
				cout << "..miniVECTOR:";
				for (it = miniExpr.begin(); it != miniExpr.end(); ++it) {
					cout << "  " << *it;
				}  cout << endl;

				for (it = miniExpr.begin(); it != miniExpr.end(); ++it) {
					cout << "   " << *it;
					// a bool
					if (*it == T || *it == F) {
						if (hasB1 && hasOp) { // if hasB1, calculate and push on vector
							if (op == AND) {
								if (toBool(*it) && toBool(b1)) *it = T;
								else *it = F;
								//*it = 
							} else {
								if (toBool(*it) || toBool(b1)) *it = T;
								else *it = F;
							}
							
							// retrieve bool-number
							cout << "  ans:" << *it << endl;
							hasResult = true;
							--it;
							hasOp = false; hasB1 = false;
							//break; // can't break in case series of operation of same sign
						} else if (hasB1) { // hasB1 but !hasOp
							cout << "Malformed: 2 num w/o operator" << endl;
							break;
						} else { // hasB1
							cout << "  setting b1" << endl;
							b1 = *it;
							hasB1 = true;
						}
					}
					else if (*it == AND) { // an AND
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
					} else if (*it == OR) { // an OR
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
					if (!hasResult) miniExpr.pop_back();
				} // end of mini expression (within ())
				// clear vector
				//for (it = miniExpr.begin(); it != miniExpr.end(); ++it) miniExpr.pop_back();
			

				// retrieve bool-number
				int ans = miniExpr.back();
				cout << " | ans:" << ans << endl;
				mystack.push(ans);
				miniExpr.pop_back();
				hasOp = false; hasB1 = false;

				/*	
				//for (it = --it; it != miniExpr.begin(); --it) { // read expr in order (which was stored backwards in vector)
				for (it = miniExpr.begin(); it != miniExpr.end(); ++it) {
					//cout << "  " << *it << endl;
					if (*it == T) {
						if (hasB1) {
							if (op == AND) {
								if (b1) numBuf = T;
								else numBuf = F;
							} else { // OR
								numBuf = T;
							}
							miniExpr.push_back(numBuf); 
							++it;
							hasB1 = false;
						} else {
							b1 = true; 
						}
					} else if (*it == F) {
						if (hasB1) {
							if (op == AND) {
								numBuf = F;
							} else {
								if (b1) numBuf = T;
								else numBuf = F;
							}
							miniExpr.push_back(numBuf);
							++it;
							hasB1 = false;
						} else {
							b1 = false;
						}
					} else if (*it == AND) { // if operator
						if (hasOp && op != AND) {
							cout << "Malformed: inconsistent op" << endl;
							break;
						}
						hasOp = true;
						op = AND;
					} else if (*it == OR) {
						if (hasOp && op != OR) {
							cout << "Malformed: inconsistent op" << endl;
							break;
						}
						hasOp = true;
						op = OR;
					}
				}
				// reset 
				hasOp = false;
				hasB1 = false;

				mystack.push(miniExpr.back()); // push bool-number to stack
				miniExpr.pop_back();
				if (!miniExpr.empty()) {
					cout << "Malformed: vector not empty" << endl;
					break;
				}*/
			} 
			
			else {// else blank space or end of expression
			}
			
		} // end of entire expression
		
		int result = mystack.top();
		mystack.pop();
		if (result == T) cout << "True" << endl;
		else cout << "False" << endl;

		if (!mystack.empty()) { // if stack isn't empty, output Malformed
			cout << "Malformed: something left still" << endl;
		}

	} // end of while loop (input file)
/*
	cout << "\nmystack: " << endl;
	
	while (!mystack.empty()) {
		cout << mystack.top() << endl;
		mystack.pop();
	}*/


	return 0;
}