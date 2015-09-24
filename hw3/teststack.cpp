// Run: g++ -g -Wall teststack.cpp stackin.cpp alistint.cpp -o teststack
#include <iostream>
#include "stackint.h"
using namespace std;

int main() {
	StackInt stack;

	for (int i=1; i<8; i++) {
		stack.push(i);
		cout << "insert: " << stack.top() << endl;
	}
	
	for (int j=1; j<8; j++) {
		stack.pop();
	}

	if (stack.empty()) cout << "SUCCESS: it's empty!" << endl;

	return 0;
}