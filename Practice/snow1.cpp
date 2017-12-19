#include <iostream>
using namespace std;
int main() {
	double snow[10000];
	int temp[10000];
	int n = 0;
	while(!cin.fail()) {
		cin >> snow[n] >> temp[n];
		n++;
	}
	
	n-= 1;
	
	double total = 0;
	for (int i = 0; i < n; i++) {
		total += snow[i];
	}

	int min = temp[0];
	for (int i = 0; i < n; i++) {
		if (min > temp[i]) {
			min = temp[i];
		}
	}

	cout << "Number of days: " << n << endl;
	cout << "Total snow: " << total << endl;
	cout << "Coldest temperature: " << min << endl;

	return 0;
}