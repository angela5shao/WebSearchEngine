#include "stackint.h"
#include <iostream>
using namespace std;

StackInt::StackInt() {

}
StackInt::~StackInt() {
	while (!this->empty()) {
		this->pop();
	}
}

bool StackInt::empty() const {
	if (list_.size() == 0) return true;
	else return false;
}

void StackInt::push(const int& val) {
	list_.insert(list_.size(), val);
}

int const &  StackInt::top() const {
	return list_[list_.size()-1];
}

void StackInt::pop() {
	if (list_.size() == 0) cout << "  Stack is empty" << endl; // if list is empty
	list_.remove(list_.size()-1);
}