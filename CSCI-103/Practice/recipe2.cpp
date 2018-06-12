#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void read(const char filename[], int *n, double numbers[], string items[]) {
	ifstream ifile(filename);

	*n = 0; 

	while (!ifile.fail()) {
		ifile >> numbers[*n] >> items[*n];
		if (!ifile.fail()) {
			*n = (*n) + 1;
		}
	}	

	ifile.close();
}

int main(int argc, char* argv[]) {
	double amount[101];
	string items[101];
	double price[101];
	string _items[101];
	int count;
	int _count;
	read(argv[1], &count, amount, items);
	read(argv[2], &_count, price, _items);

	bool impossible = false;
	double total = 0;
	for (int i = 0; i < count; i++) {
		bool found = false;
		for (int j = 0; j < _count; j++) {
			if (items[i] == _items[j]) {
				total += amount[i] * price[j];
				found = true;
			}
		}
		if (found == false) {
			impossible = true;
		}
	}
	
	if (impossible) {
		cout << "impossible" << endl;
	}
	else {
		cout << total << endl;
	}

	return 0;
}