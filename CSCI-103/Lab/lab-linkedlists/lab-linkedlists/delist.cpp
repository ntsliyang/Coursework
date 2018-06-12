#include "delist.h"
#include <iostream>
using namespace std;

// initialize an empty list
DEList::DEList() {
	head = NULL;
	tail = NULL;
}

// destructor (free all of memory for each item)
DEList::~DEList() {
	while (!empty()) {
		pop_front();
	}
}

// return true if the list is empty
bool DEList::empty() {
	return (head == NULL || tail == NULL);
}

// return the number of items in the list
int DEList::size() {
	int cnt = 0;
	DEItem *temp = head;
	while (head != NULL && temp != 0)
	{
	  cnt++;
	  temp = temp->next;
	}
	return cnt;
}

// return the item value at the front of the list 
int DEList::front() {
	if (head != NULL) return head->val;
	else return -1;
}

// return the item value at the back of the list
int DEList::back() {
	if (tail != NULL) return tail->val;
	else return -1;
}

// create a new DEItem at the front of the list
// push every other item back 

// create a new DEItem at the front of the list 
// new DEItem has val of new_val and next of head
// so the current head has the DEItem has new_item
// and that's for head (next) ordering 
// but for tail (prev) ordering, that's the same as push_back
void DEList::push_front(int new_val) {
	DEItem* new_item = new DEItem;
	new_item->val = new_val;
	new_item->prev = NULL;
	if (head) {
		new_item->next = head;
		head->prev = new_item;	
		head = new_item;
	}
	else {
		head = new_item;
		head->next = NULL;
		tail = head;
	}

}

// add a new_val at the back of the list 
// assign new_val and DEItem for new_item 
// so next for new_item is 0
// so prev for new_item is tail
// change the old tail into new_item 
// if head is equal to tail, which means it is an empty list 
// head equals to tail, and they equal to new_item 
// 
void DEList::push_back(int new_val) {
	DEItem* new_item = new DEItem;
	new_item->val = new_val;
	new_item->next = NULL;
	if (tail) {
		tail->next = new_item;
		new_item->prev = tail;
		tail = new_item;
	}
	else {
		tail = new_item;
		tail->prev = NULL;
		head = tail;
	}
}

// remove the front item if there is one
void DEList::pop_front() {
	if (!empty()) { // only remove if list is not empty 
		DEItem* temp = head;
		if (head->next != NULL) {
			head->next->prev = NULL;
			head = temp->next;
		}
		else {
			tail = head = NULL;
		}
		delete temp;
	}
}

// remove the back item if there is one
void DEList::pop_back() {
	if (!empty()) {
		DEItem* temp = tail;
		if (tail->prev != NULL) {
			tail->prev->next = NULL;
			tail = temp->prev;
		}
		else {
			head = tail = NULL;
		} 
		delete temp;
	}
}