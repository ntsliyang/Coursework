#include "lliststr.h"
#include <iostream>

LListStr::LListStr() {
	head_ = tail_ = NULL;
	size_ = 0;
}

LListStr::~LListStr() {
	int s = size();
	for (int i = 0; i < s; i++) {
		remove(0);
	}
	size_ = 0; 
}

int LListStr::size() const {
	return size_;
/*
	if (head_ == NULL) return 0;
	Item* temp = head_;
	int cnt = 0;
	do {
		cnt++;
		temp = temp->next;
	} while (temp != head_);
	return cnt;
*/
}

bool LListStr::empty() const {
	return (size_ == 0);
}

void LListStr::insert(int pos, const std::string &val){
	if (pos > size_ || pos < 0) return;
	Item* new_item = new Item;
	new_item->val = val;
	if (size_ == 0) {
			head_ = tail_ = new_item;
			new_item->next = head_;
			new_item->prev = tail_; 
			size_++;
			return;
	}
	else {
		if (pos == 0) { 
			head_->prev = new_item;
			tail_->next = new_item;
			new_item->next = head_;
			new_item->prev = tail_;
			head_ = new_item;
			size_++;
			return;
		} // insert at the head 
		else if (pos == size_) {
			tail_->next = new_item;
			head_->prev = new_item;
			new_item->prev = tail_;
			new_item->next = head_;
			tail_ = new_item;
			size_++;
			return;
		} // insert at the end 
		else {
			Item* temp = head_;
			int cnt = 0;
			while (true) {
				cnt++;
				temp = temp->next;
				if (cnt == pos) {
					new_item->prev = temp->prev;
					new_item->next = temp;
					temp->prev->next = new_item;
					temp->prev = new_item;
					size_++;
					return;
				}
			}
		}
	}
}

void LListStr::remove(int pos) {
	if (pos >= size_ || pos < 0) return;
	if (head_ == NULL) return; // empty list
	size_--;
	if (pos == 0) {
		tail_->next = head_->next;
		head_->next->prev = tail_;
		Item* temp = head_;
		head_ = temp->next;
		delete temp;
		return;
	} // remove the head of the list
	else {
		if (pos == size_) {
			tail_->prev->next = head_;
			head_->prev = tail_->prev;
			Item* p = tail_;
			tail_ = p->prev;
			delete p;
			return;
		} // remove the tail of the list
		else {
			Item* temp = head_; 
			int cnt = 0;
			while (true) {
				cnt++;
				temp = temp->next;
				if (cnt == pos) {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					delete temp;
					return;
				} // remove the element at posth position
			}
		}
	}
	return;
}

void LListStr::set(int pos, const std::string &val) {
	if (pos >= size_ || pos < 0) return;
	Item* temp = head_;
	int cnt = 0;
	while (true) {
		if (cnt == pos) {
			if (temp) {
				temp->val = val;
				return;
			}
		}
		cnt++;
		temp = temp->next;
	}
	return;
}

std::string LListStr::get(int pos) const {
	std::string str;
	if (pos >= size_ || pos < 0) return str;
	Item* temp = head_;
	if (pos == 0) return head_->val;
	int cnt = 0;
	do {
		cnt++;
		temp = temp->next;
		if (cnt == pos) {
			str = temp->val;
			break;
		}
	} while (temp != head_);
	return str;
}