#include <iostream>
using namespace std;

bool isD(int* r, int length) {
	for (int i = 1; i <= length; i++) {
		if (r[i] == i) {
			return false;
		}
	}

	return true;
}

int main() {
	int n;
	cin >> n;
	int* temp = new int [n + 1];
	int m = 0;
	bool first = false;
	while(!cin.fail()) {
		for (int i = 1; i <= n; i++) {
			cin >> temp[i];
		}
		if (!cin.fail()) {
			if (first == true && isD(temp, n) == true) {
				m++;
			}	
			else if (isD(temp, n) == true) {
				first = true;
				cout << "First derangement: ";
				for (int i = 1; i <= n; i++) {
					cout << temp[i] << ' ';
				}
				cout << endl;
				m++;
			}
		}
	}

	cout << "Number of derangements: " << m << endl;
	

	delete [] temp;
	return 0;
}