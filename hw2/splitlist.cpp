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
	//Node* const head = in;
	// base case
	if (in == NULL) {
		smaller = NULL;
		larger = NULL;
		return;
	}

	if (in->value <= pivot) {
		smaller = in; // set ptr smaller to ptr in
		Node* next= in->next;
		in = NULL;
		split(next, smaller->next, larger, pivot);
	} else {
		larger = in; // set ptr smaller to ptr in
		/*if (larger == NULL) {
			Node* next = in->next;
			in = NULL;
			split(next, smaller, larger->next, pivot);
		} else {
			split(in->next, smaller, larger->next, pivot);
		}*/
		Node* next= in->next;
		in = NULL;
		split(next, smaller, larger->next, pivot);
	}
}

int main(int argc, char* argv[]) {
	//Node* myNode = new Node;
	Node* head = NULL;
	Node* curr = NULL;

	// fill list
	srand(time(0));

	for (int i=0; i<3; i++) {
		// create new Node
		Node* newNode = new Node;
		newNode->value = rand() % 20;

		// if it's the first Node (head), set head to it
		if (i == 0) {
			head = newNode;
			curr = head;
		} else {
			curr->next = newNode;
			curr = curr->next;
		}
	}
	// print list
	for (Node *p = head; p != NULL; p=p->next) {
		cout << p->value << endl;	
	}

	Node* smaller = NULL;
	Node* larger = NULL;
	int pivot = 10;
	split (head, smaller, larger, pivot);



	// TEST: print smaller & larger lists
	cout << "smaller list: ";
	for (Node *s = smaller; s != NULL; s=s->next) 
		cout << s->value << " ";
	cout << endl;

	cout << "larger list: ";
	for (Node *l = larger; l != NULL; l=l->next) 
		cout << l->value << " ";
	cout << endl;

	if (head == NULL) {
		cout << "SUCCESS: head = NULL" << endl;
	} else {
		cout << "FAIL: head isn't NULL, value = " << head->value << endl;
	}


	// delete dynamic memory
	for (Node *q = head; q != NULL; q=q->next) {
		delete q;
	}

	return 0;
}