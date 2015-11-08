#include <vector>
#include <iostream>
using namespace std;

template <class T, class Comparator>
void Merge(vector<T>& myArray, int l, int m, int r, Comparator comp) {
	vector<T> temp;
	int i = l, j = m+1, k = 0;
	while (i <= m || j <= r) { // at least one subarray contains another element 
		if (i <= m && (j > r || comp(myArray[i], myArray[j]) ))	{ 
			temp.push_back(myArray[i]); i ++; k ++; 
	 	} else { 
	 		temp.push_back(myArray[j]); j ++; k ++; 
	 	}
	}
	// now copy over the merged array into the original
	for (k = 0; k < r+1-l; k ++){
		myArray[k+l] = temp[k];
	}
}

template <class T, class Comparator>
void MergeSort(vector<T>& myArray, int l, int r, Comparator comp){
	if (l>=r) return; // otherwise, just one element, which is sorted
	int m = (l+r)/2;
	MergeSort(myArray, l, m, comp);
	MergeSort(myArray, m+1, r, comp);
	Merge(myArray, l, m, r, comp); // this is a separate function given below
	
}

template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp) {
	MergeSort(myArray, 0, myArray.size()-1, comp);
}

/* 
// submitted version - DOESN'T WORK
#include <vector>
#include <iostream>
using namespace std;

template <class T, class Comparator>
void Merge(vector<T>& myArray, int l, int r, int m, Comparator comp)
{
	vector<T> temp;
	int i = l, j = m+1, k = 0;
	while (i <= m || j <= r) { // at least one subarray contains another element 
		if (i <= m && (j > r || comp(myArray[i], myArray[j]) ))	{ 
			temp.push_back(myArray[i]); i ++; k ++; 
	 	} else { 
	 		temp.push_back(myArray[j]); j ++; k ++; 
	 	}
	}
	// now copy over the merged array into the original
	for (k = 0; k < r+1-l; k ++){
		myArray[k+l] = temp[k];
	}
}

template <class T, class Comparator>
void MergeSort(vector<T>& myArray, int l, int r, Comparator comp)
{
	
	if (l>=r) return; // otherwise, just one element, which is sorted
	int m = (l+r)/2;
	MergeSort(myArray, l, m, comp);
	MergeSort(myArray, m+1, r, comp);
	Merge(myArray, l, m, r, comp); // this is a separate function given below
	
}

template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp)
{
	
	MergeSort(myArray, 0, myArray.size()-1, comp);
}*/

/*
#include <iostream> // to test
#include <vector>
using namespace std;

template <class T, class Comparator>
void merge(vector<T>& a, int l, int r, int m, Comparator comp) {
	vector<T> temp;
	int i = l, j = m+1, k=0; 
	while (i <= m || j <= r) { // at least one subarray is not empty
		if (i <= m && (j > r || comp(a[i], a[j]))) { 
			temp.push_back(a[i]); 
			i++; k++;
		} else {
			temp.push_back(a[j]); 
			j++; k++;
		}
	}
	for (k=0; k< r+l-1; k++)
		a[k+l] = temp[k];
}

template <class T, class Comparator>
void mergeSortHelper(vector<T>& a, int l, int r, Comparator comp) {
	if(l>=r)
        return;

		int m = (l+r)/2;
		mergeSortHelper(a, l, m, comp);
		mergeSortHelper(a, m+1, r, comp);
		merge(a, l, r, m, comp);	
}

template <class T, class Comparator>
void mergeSort(vector<T>& myArray, Comparator comp) {
	int r = myArray.size() -1;
	int l = 0;
	mergeSortHelper(myArray, l, r, comp);
}
*/






/*
#include <iostream>
#include <vector>
#include "msort.h"
using namespace std;

class AlphaStrComp {
  public:
	bool operator()(const string& lhs, const string& rhs) {
		return lhs < rhs;
	}
};

class LengthStrComp {
  public:
	bool operator() (const string& lhs, const string& rhs) {
		return lhs.size() < rhs.size();
	}
};

class LTComp {
  public:
  	bool operator() (const int& lhs, const int& rhs) {
  		return lhs < rhs;
  	}
};

int main(int argc, char* argv[]) {
	string s1 = "Blue";
	string s2 = "Red";

	AlphaStrComp comp1;
	LengthStrComp comp2;
	cout << s1 << " compared to " << s2 << " using AlphaStrComp = " << comp1(s1, s2) << endl;
	cout << s1 << " compared to " << s2 << " using LengthStrComp = " << comp2(s1, s2) << endl;

	vector<int> intArrO;
	intArrO.push_back(9);
	intArrO.push_back(5);
	intArrO.push_back(1);
	intArrO.push_back(3);
	intArrO.push_back(7);

	LTComp ltComp;
	mergeSort(intArrO, ltComp);

	for (int i=0; i<5; i++)
		cout << intArrO[i] << endl; 

	return 0;
}
*/