#include "llistint.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  LListInt * list = new LListInt();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  list->remove(0);
  if (list->size() == 0) {
    cout << "SUCCESS: List has size 0 after removal of nonexistent Item." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after incorrect removal.";

  // Insert an item at the head.
  list->insert(0, 3);
  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }
  // Check if the value is correct.
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  list->insert(1, 10);
  if (list->size() == 2) {
    cout << "SUCCESS: List has size 2 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
    cout << endl;
  }
  if (list->get(1) == 10) {
    cout << "SUCCESS: 10 is at 1st index of the list." << endl;
  } else {
    cout << "FAIL: 10 is not at the 1st index of the list, " << list->get(1) << " is instead" << endl;
  }


  list->remove(0);
  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after removal of 0th Node, ";
    cout << "which now has value: " << list->get(0) << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after removal of 0th Node." << endl;
  }

  list->remove(0);
  if (list->empty()) {
    cout << "SUCCESS: List is empty after removal." << endl;
  } else {
    cout << "FAIL: List is not empty after removal." << endl;
  }
  cout << "size after removal of Item: " << list->size() << endl;

  // Clean up memory.
  delete list;
}
