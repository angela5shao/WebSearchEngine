/* Problem 6: implement doubly-linked list
*/
#include "llistint.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream> // for testing
using namespace std;

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val) {
  // check bounds; if not, return
  if (loc < 0 || loc > size_)
    return;

  // create new Item; set its value
  Item* newItem = new Item; 
  newItem->val = val;

  if (size_ == 0) { // if list is empty
    // update head and tail to newItem
    head_ = newItem; 
    newItem->next = NULL;
    tail_ = head_;
  } else if (loc == size_) { // if loc is past last node (need to append)
    Item* locItem1 = getNodeAt(size_ - 1); // get ptr to last Item
    locItem1->next = newItem;
    newItem->next = NULL;
    tail_ = newItem; // update tail_
  } else {
    Item* locItem2 = getNodeAt(loc); // retrieve ptr to current Item at loc
    // update previous Item's next (as newItem)
    locItem2->prev->next = newItem;
    // update newItem's previous & next
    newItem->prev = locItem2->prev;
    newItem->next = locItem2;
    // update locItem's previous (as newItem)
    locItem2->prev = newItem;
  }

  size_++; // update size of list
}

/**
 * Complete the following function
 */
void LListInt::remove(int loc) {
  // if list is empty or loc not within bounds, return
  if (this->empty() || loc < 0 || loc > size_ - 1)
    return;

  // get ptr to loc-th Item
  Item* ItemToRem = getNodeAt(loc);
  if (size_ == 1) { // if there's only 1 Item
    delete head_;
    head_ = NULL;
    tail_ = NULL;
  } else if (ItemToRem == head_) { // if it's the head
    Item* headNext = head_->next;
    delete head_;
    head_ = headNext;
    head_->prev = NULL;
  } else if (ItemToRem == tail_) { // if it's the tail
    Item* beforeTail = tail_->prev;
    delete tail_;
    tail_ = beforeTail;
    tail_->next = NULL;
  } else {
    ItemToRem->prev->next = ItemToRem->next; // update ItemToRem's previous
    ItemToRem->next->prev = ItemToRem->prev; // update ItemToRem's next
    delete ItemToRem; // delete
  }
  size_--; // update size (supposedly 0)
}

void LListInt::set(int loc, const int& val) {
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc) {
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const {
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear() {
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


/**
 * Locates Item at location loc; returns pointer to the Item
 */
LListInt::Item* LListInt::getNodeAt(int loc) const {
  Item* result = NULL;
  // if list is empty or loc not within range, return NULL
  if ((size_ == 0) || (loc >= size_)) {
    return result;
  }

  // traverse to loc-th Item
  result = head_;
  for (int i=0; i<loc; i++) {
    result = result->next;
  }
  return result;
}
