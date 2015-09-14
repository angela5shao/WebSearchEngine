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

  // Insert an item at the head.
  list->insert(0, 3);

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  list->remove(1);

  // Check if the list is empty.
  if (list->empty()) {
    cout << "FAIL: List is empty after removing nonexistent Item." << endl;
  } else {
    cout << "SUCCESS: List is not empty after removal of nonexistent Item." << endl;
  }

  list->remove(0);
  if (list->empty()) {
    cout << "SUCCESS: List is empty after removal." << endl;
  } else {
    cout << "FAIL: List is not empty after removal." << endl;
  }

  // Clean up memory.
  delete list;
}
