#include <iostream>
#include <cstdio>
#include <deque>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <array>
#include <sstream>
#include <iomanip>
#include <deque>
using namespace std;

struct Item {
	int val;
	Item* next;
}

void deleteSecond(Item* head) {
	if (head == NULL || head->next == NULL) {
		return;
	}
	else {
		Item* secondItem = head->next;
		head->next = head->next->next;
		delete secondItem;
	}
}

int* zip(int* arr1, int* arr2, int len) {
	int pos = 0;
	int* arr = new int [2*len];
	for (int i = 0; i < len; i++) {
		arr[pos++] = arr1[i];
		arr[pos++] = arr2[i];
	}

}

int** unzip(int* arr, int len) {
// int* unzip(int* arr, int len, int*& arr2)
	int pos = 0;
	int** ar = new int* [2];
	for (int i = 0; i < 2; i++) {
		int* arr = new int [len/2];
	}
	for (int i = 0; i < len; i++) {
		
	}	 
}

class Change {
public: 
	Change(int total);
	int getQuarters();
	int getDimes();
	int getNickels();
	int getPennies();
	string toString();
private:
	int q, d, n, p;
}

Change::Change(int total) {
	q = total / 25;
	total %= 25;
	d = total / 10;
	total %= 10;
	n = total / 5;
	total %= 5;
	p = total;
}

string Change::toString() {
	stringstream ss;
	ss << "Q: " << q << ", D: " << d << ", N: " << n << ", P: " << p;
	return ss.str();
}

void mystery(int n, int i, string pre) {
	if (i == n) {
		cout << pre << endl;
	}
	else {
		if (i % 2 == 0) {
			for (int k = 0; k < 2; k++) {
				mystery(n, i +1, pre + ('a' + k));
			}
		else {
			for (int k = 0; k < 3; k++) {
				mystery(n, i + 1, pre + ('0' + k));
			}
		}
		}
	}
}

mystery(3, 0, "");
