#ifndef MYSET_H
#define MYSET_H

#include <set>
#include <string>

class WebPage;

/*class MySetString : public std::set<std::string>
{
public:
  MySetString();
  MySetString set_intersection(const MySetString& other);
  MySetString set_union(const MySetString& other);
};

class MySetWebPage : public std::set<WebPage*>
{
public:
  MySetWebPage();
  MySetWebPage set_intersection(const MySetWebPage& other);
  MySetWebPage set_union(const MySetWebPage& other);
};*/


template<class T>
class myset : public std::set<T> {
public: 
	myset<T>() {};
	myset<T> set_intersection(const myset<T>& other) {
		myset<T> newSet;
		typename std::set<T>::iterator it;

		// for all string in other, see if count in this is 1 (exists)
		for (it = this->begin(); it != this->end(); ++it) {
			if (other.count(*it) == 1) {
				newSet.insert(*it);
			}
		}
		return newSet;
	}

	myset<T> set_union(const myset<T>& other) {
		myset<T> newSet; // create new mySetString object
		typename std::set<T>::iterator it;

		// add this and other into it
		for (it = this->begin(); it != this->end(); ++it) {
			newSet.insert(*it);
		}
		for (it = other.begin(); it != other.end(); ++it) {
			newSet.insert(*it);
		}
		return newSet;
	}
};

#endif
