#include "lliststr.h"
#include <iostream>
using namespace std;

void checkEmpty(LListStr *list, bool expEmpty) {
	if (list->empty() == expEmpty) {
		cout << "SUCCESS: List is ";
		if (!expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
	else {
		cout << "FAIL: List is ";
		if (expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
}

void checkSize(LListStr *list, int expSize) {
	int size = list->size();
	if (size == expSize) {
		cout << "SUCCESS: List has size " << size << endl;
	}
	else {
		cout << "FAIL: List has size " << size;
		cout << " but expected " << expSize << endl;
	}
}

void checkGet(LListStr *list, int pos, const string &expStr) {
	string str = list->get(pos);
	if (str == expStr) {
		cout << "SUCCESS: String at index " << pos << " is \'" << expStr << "\'" << endl;
	} 
	else {
		cout << "FAIL: String at index " << pos << " is \'" << str << "\'";
		cout << " but expected \'" << expStr << "\'" << endl;
	}
}

void checkSet(LListStr *list, int pos, const string &expStr) {
	string sstr = list->get(pos);
	if (sstr == expStr) {
			cout << "SUCCESS: String at index " << pos << " is \'" << expStr << "\'" << endl;
	} 
	else {
		cout << "FAIL: String at index " << pos << " is \'" << sstr << "\'";
		cout << " but expected \'" << expStr << "\'" << endl;
	}
}

int main() {
	LListStr* list = new LListStr();
	checkEmpty(list, true);
	checkSize(list, 0);

	list->insert(0, "a"); // 1: a
	list->insert(0, "b"); // 0: b
	list->insert(5, "c");
	list->insert(3, "d");
	checkSize(list, 2);
	list->remove(3);
	list->insert(4, "e");
	list->insert(2, "f"); // 2: f
	checkSize(list, 3);
	list->remove(3); 
	list->remove(2);
	checkSize(list, 2);
	list->insert(2,"k");
	list->set(2, "h"); // 2: h
	checkSet(list, 2, "h");
	list->set(0, "z");
	checkSet(list, 0, "z");
	list->set(2, "l");
	list->set(3, "i");
	list->set(4, "j");
	list->get(4); 
	list->get(2);
	checkGet(list, 2, "l");
	delete list;
	return 0;

}