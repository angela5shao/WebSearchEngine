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
*/
void split (Node*& in, Node*& smaller, Node*& larger, int pivot) {
	// base case
	if (in == NULL) return;

	if (in->value <= pivot) {
		cout << "svalue: " << in->value << endl;

		smaller = in; // set ptr smaller to ptr in
		//cout << " smaller->value: " << smaller->value << endl;

		// call split with smaller->next
		split(in->next, smaller->next, larger, pivot);
		// save in->next
	} else {
		cout << "lvalue: " << in->value << endl;

		larger = in; // set ptr smaller to ptr in
		//cout << " smaller->value: " << smaller->value << endl;

		// call split with smaller->next
		split(in->next, smaller, larger->next, pivot);
	}
}

int main(int argc, char* argv[]) {
	Node* myNode = new Node;
	Node* head = myNode;

	srand(time(0));
	for (int i=0; i<3; i++) {
		myNode->value = rand() % 20;

		Node* newNode = new Node;
		myNode->next = newNode;
		myNode = myNode->next;
	}

	for (Node *p = head; p != NULL; p=p->next) {
		cout << p->value << endl;	
	}

	Node* smaller = new Node;
	Node* larger = new Node;
	int pivot = 10;
	split (head, smaller, larger, pivot);

	return 0;
}