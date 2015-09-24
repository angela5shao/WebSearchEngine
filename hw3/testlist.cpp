#include <iostream>
#include "alistint.h"
using namespace std;

int main() {

	AListInt list2;
	AListInt* listA = new AListInt;

	list2.insert(0, 100);
	//cout << "size (==1): " << list2.size() << endl;

	for (int j=0; j<5; j++) {
		listA->insert(j, 10+j);
		//cout << "size: " << listA->size() << endl;
	}

	list2 = *listA;
	delete listA;

	for (int i = 0 ; i < 5; i++) {
		//cout << "loop " << i << " ..." << endl;
		if (list2.get(i) == 10+i) {
			cout << "  [" << i << "] == " << 10+i << endl;
		} else {
			cout << "  NOT EQUAL" << endl;
		}
	}

	// TEST remove
	for (int k=0; k<5; k++) {
		list2.remove(list2.size()-1);
	}

	if (list2.empty()) cout << "SUCCESS: list is empty" << endl;
	else cout << "FAIL: list isn't empty" << endl;

	AListInt list3 = list2 + list2;
	if (list3.size() == 10) cout << "SUCCESS: added two lists" << endl;
	else cout << "FAIL: added list size incorrect" << endl;

	return 0;
}