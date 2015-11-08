#include "myset.h"
#include "webpage.h"

#include <iostream>
using namespace std;

MySetString::MySetString() : std::set<std::string>() {}

MySetString MySetString::set_intersection(const MySetString& other) {
	MySetString newSet;
	std::set<std::string>::iterator it;

	// for all string in other, see if count in this is 1 (exists)
	for (it = this->begin(); it != this->end(); ++it) {
		if (other.count(*it) == 1) {
			newSet.insert(*it);
		}
	}
	return newSet;
}

MySetString MySetString::set_union(const MySetString& other) {
	MySetString newSet; // create new mySetString object
	std::set<std::string>::iterator it;

	// add this and other into it
	for (it = this->begin(); it != this->end(); ++it) {
		newSet.insert(*it);
	}
	for (it = other.begin(); it != other.end(); ++it) {
		newSet.insert(*it);
	}
	return newSet;
}


MySetWebPage::MySetWebPage() : std::set<WebPage*>() {}

MySetWebPage MySetWebPage::set_intersection(const MySetWebPage& other) {
	MySetWebPage newSet;
	std::set<WebPage*>::iterator it;

	// for all string in other, see if count in this is 1 (exists)
	for (it = this->begin(); it != this->end(); ++it) {
		if (other.count(*it) == 1) {
			newSet.insert(*it);
		}
	}

	return newSet;
}

MySetWebPage MySetWebPage::set_union(const MySetWebPage& other) {
	MySetWebPage newSet; 
	std::set<WebPage*>::iterator it;

	// add this and other into it
	for (it = this->begin(); it != this->end(); ++it) {
		newSet.insert(*it);
	}
	for (it = other.begin(); it != other.end(); ++it) {
		newSet.insert(*it);
	}

	return newSet;
}
