#include <iostream>
#include "alistint.h"
using namespace std;

int main() {
	/*AListInt list;
	for (int i=0; i<4; i++) {
		list.insert(i, 10+i);
	}
	for (int j=0; j<5; j++) {
		cout << list[j] << " ";
	} cout << endl;*/



	AListInt list2;
	AListInt* listA = new AListInt;

	list2.insert(0, 100);
	//cout << "size (==1): " << list2.size() << endl;

	for (int j=0; j<5; j++) {
		listA->insert(j, 10+j);
		//cout << "size: " << listA->size() << endl;
	}

	list2 = *listA;
	//cout << "size of list: " << list2.size() << endl;

	delete listA;
	//cout << "finished deleting temp list" << endl;

	for (int i = 0 ; i < 5; i++) {
		//cout << "loop " << i << " ..." << endl;
		if (list2.get(i) == 10+i) {
			cout << "  [" << i << "] == " << 10+i << endl;
		} else {
			cout << "  NOT EQUAL" << endl;
		}
	}

	return 0;
}