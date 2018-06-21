#include "stackstr.h"
#include <iostream>

StackStr::StackStr() {}

StackStr::~StackStr() {}

bool StackStr::empty() const {
	return (list_.empty());
}

int StackStr::size() const {
	return (list_.size());
}

void StackStr::push(const std::string &str) {
	list_.insert(list_.size(), str);
}

std::string StackStr::top() const {
	return list_.get(list_.size() - 1);
}

void StackStr::pop() {
	if (!list_.empty()) {
		list_.remove(list_.size() - 1);
	}
}