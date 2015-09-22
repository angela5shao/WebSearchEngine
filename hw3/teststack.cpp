#include <iostream>
#include "stackint.h"
using namespace std;

int main() {
	StackInt stack;
	stack.push(10);
	cout << "top: " << stack.top() << endl;

	return 0;
}