#include "alistint.h"

#include <iostream>

using namespace std;

AListInt::AListInt() {
	_data = new int[5];
	_size = 0;
	_cap = 5;
}

AListInt::AListInt(int cap) {
	_data = new int[cap];
	_size = 0;
	_cap = cap;
}

AListInt::AListInt(const AListInt& other) {
	// WATACH OUT: i) already initialized destination (this), ii) self assignment
	if (this == &other) return; // why &: compare addr of this object and addr of other object
	if (_data) {
		for (unsigned int k=0; k<this->_size; k++) delete &_data[k];
	}

	// copy size, capacity, content
	this->_size = other._size;
	this->_cap = other._cap;
	this->_data = new int[this->_size];
	for (unsigned int i=0; i<this->_size; i++) {
		this->_data[i] = other._data[i];
	}
}

AListInt& AListInt::operator=(const AListInt& other) {
	if (this == &other) return *this; // why &: compare addr of this object and addr of other object
	if (_data) {
		for (unsigned int k=0; k<this->_size; k++) delete &_data[k];
	}

	this->_size = other._size;
	this->_cap = other._cap;
	this->_data = new int[this->_size];
	for (unsigned int i=0; i<this->_size; i++) {
		this->_data[i] = other._data[i];
	}
	return *this;
}

AListInt::~AListInt() {
	for (unsigned int i=0; i<_size; i++) {
		delete &_data[i];
	}
	_data = NULL;
	_size = 0;
	_cap = 0;
}
  
int AListInt::size() const {
	return _size;
}

bool AListInt::empty() const {
	if (_size == 0) return true;
	else return false;
}

void AListInt::insert (int pos, const int& val) {
	// if appending
	if (pos >= _cap) {
		// resize (_cap doubled); update _cap and _size?????????
		this->resize();
	}
	_data[pos] = val;
}

void AListInt::remove (int pos) {
	if (this->empty()) return; // if list is empty

	delete &_data[pos];
	_size--;
}

void AListInt::set (int position, const int& val) {
	_data[position] = val;
}

int& AListInt::get (int position) {
	return _data[position];
}

int const & AListInt::get (int position) const { // ????? same func???
	return _data[position];
}

AListInt AListInt::operator+(const AListInt& other) const {
	AListInt newList(this->_size + other._size); // capacity is same as combined size
	for (unsigned int i=0; i<this->_size; i++) {
		newList._data[i] = this->_data[i];
	}
	for (unsigned int j=this->_size; j<other._size; j++) {
		newList._data[j] = other._data[j];
	}
	newList._size = newList._cap;
	return newList;
}
  
int const & AListInt::operator[](int position) const {
	return this->_data[position];
}

int& AListInt::operator[](int position) {
	return this->_data[position];
}