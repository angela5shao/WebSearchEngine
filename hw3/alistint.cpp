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
	if (this == &other) return; // if self assignment

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
	if (!this->empty()) {
		//for (unsigned int k=0; k<this->_size; k++) delete &_data[k];
		//for (unsigned int k=0; k<this->_size; k++) remove(k);
		delete [] this->_data;
	}

	this->_size = other._size;
	this->_data = new int[other._cap];
	this->_cap = other._cap;
	for (unsigned int i=0; i<other._size; i++) {
		this->_data[i] = other._data[i];
	}
	return *this;
}

AListInt::~AListInt() {
	delete [] _data;
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
	if (_size == _cap) { // if out of space 
		resize(); 
	}
	if ( (unsigned)pos > _cap || pos < 0) { // if out of bounds, do nothing
		cout << "    inserting out of bounds" << endl;
		return; 
	}

	_size++;
	for (unsigned int i=_size-1; i>(unsigned)pos; i--) { // shift everything after pos back by one
		cout << "   shift ["<<i<<"]=["<<i-1<<"]" << endl;
		_data[i] = _data[i-1];
	}
	_data[pos] = val;

	/*if (empty()) {
		//_data[pos] = val;
		set(pos, val);
	} else {
		for (unsigned int i=_size-1; i>(unsigned)pos; i--) { // shift everything after pos back by one
			_data[i] = _data[i-1];
		}
	}*/
}

void AListInt::remove (int pos) {
	if (empty()) return; // if list is empty
	if ( (unsigned)pos > _size-1 || pos < 0) return; // if out of bounds, do nothing

	for (unsigned int i=pos; i<_size-1; i++) { // shift everything after pos up by one
		_data[i] = _data[i+1];
	}
	_size--;
}

void AListInt::set (int position, const int& val) {
	if (((unsigned)position > _size-1) || (position < 0)) return; // if out of bounds
	_data[position] = val;
}

int& AListInt::get (int position) {
	if (((unsigned)position > _size-1) || (position < 0)) return _data[0]; // if out of bounds
	return _data[position];
}

int const & AListInt::get (int position) const { // ????? same func???
	if (((unsigned)position > _size-1) || (position < 0)) return _data[0]; // if out of bounds
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
	return _data[position];
}

int& AListInt::operator[](int position) {
	if ( (unsigned)position > _size-1 || position < 0) return _data[0]; // out of bounds
	return _data[position];
}

void AListInt::resize() {
	/*AListInt newList;
	newList._data = new int[this->_cap * 2]; // double capacity
	newList._size = this->_size; 
	for (unsigned int i=0; i<this->_size; i++) { // maintain original data
		newList._data[i] = this->_data[i];
	}

	// delete original
	delete [] this->_data;

	*this = newList;*/
	_cap *= 2;
	int* newData = new int[_cap]; // double capacity
	for (unsigned int i=0; i < _size; i++) { // maintain original data
		newData[i] = _data[i];
	}
	delete [] _data;
	_data = newData;
}