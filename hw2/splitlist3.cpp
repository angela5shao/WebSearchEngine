/* Problem 5:  */
#include <iostream>
#include <cstdlib>
using namespace std;

struct Node {
	int value;
	Node *next;
};

/* Purpose: splits list "in" to smaller list for elements <= pivot and larger list for elements > pivot
param: pointers to list "in", "smaller", "larger", and int pivot
return: none
*/
void split (Node*& in, Node*& smaller, Node*& larger, int pivot) {
	if (in == NULL) {
		smaller = NULL;
		larger = NULL;
	} else {
		cout << "taking in: " << in->value;
		if (in->value <= pivot) {
			cout << "  smaller.." << endl;
			if (smaller == NULL) {
				smaller = in;
			} else {
				smaller->next = in;
			}
			split(in->next, smaller->next, larger, pivot);
		} 
		else { 
			cout << "  larger.." << endl;
			split(in->next, smaller, larger, pivot);
		}
	}
	
}

int main(int argc, char* argv[]) {
	Node* myNode = new Node;
	Node* head = myNode;

	srand(time(0));
	for (int i=0; i<6; i++) {
		myNode->value = rand() % 20;
		Node* newNode = new Node;
		myNode->next = newNode;
		myNode = myNode->next;
	}

	myNode = NULL;
	for (Node *p = head; p->next != NULL; p=p->next) {
		cout << p->value << endl;	
	}

	Node* smaller = NULL; //new Node;
	Node* larger = NULL;//new Node;
	int pivot = 10;

	cout << "setting:" << endl;
	smaller = myNode;
	//smaller->value = 0;
	cout << "value: " << smaller->value << endl;

	
	//split (head, smaller, larger, pivot);
/*
// TESTING
	cout << "\nsmaller list: " << endl;
	while (smaller) {
		cout << smaller->value << " ";
		smaller = smaller->next;
	} 

	cout << "\nlarger list: " << endl;
	while (larger->next) {
		cout << larger->value << " ";
		larger = larger->next;
	} */

	return 0;
}