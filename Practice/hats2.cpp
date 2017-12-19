#include <iostream>
using namespace std;

int maxCycleLength(int arr[], int N) {
	int max = 0;
	int cycle;
	for (int i = 0; i < N; i++) {
		cycle = 1;
		int j = i;
		while (arr[j] != i + 1) {
			j = arr[j] - 1;
			cycle++;
		}
		
		if (max < cycle) {
			max = cycle; 
		}
	}	

	return max;
}
int main() {
	int n;
	cin >> n;
	int* temp = new int [n + 1];
	double total = 0.0;
	double count = 0.0;
	while(!cin.fail()) {
		for (int i = 0; i < n; i++) {
			cin >> temp[i];
		}
		if (!cin.fail()) {
			total += maxCycleLength(temp, n);	
			count++;
		}
	}
	double avg = total / count;
	cout << "Average max cycle length: " << avg << endl;
	delete [] temp;
	return 0;
}