#include <iostream>
using namespace std;
int main () {
	int list[] = {13, 9, 6, 3, 15, 2, 21, 4, 16, 8, 11};

	for (int i = 0; i < 10; i++) {
		int smallest = i;
		int num = 0;
		for (int j = i + 1; j < 11; j++) {
			if (list[j] < list[smallest]) {
				cout << "Compare " << list[j] << " to " << list[smallest] << "; ";
				cout << list[j] << " < " << list[smallest] << ", ";
				cout << "so the lowest value is " << list[j] << ".";
				cout << " Therefore, the two values are swapped." << endl;
				smallest = j;
				num++;
			}

			else {
				cout << "Compare " << list[j] << " to " << list[smallest] << "; ";
				cout << list[j] << " > " << list[smallest] << ", ";
				cout << "so the lowest value is still " << list[smallest] << ".";
				cout << " Therefore, there is no swap." << endl;
				num++;
			}
		}
		cout << "Number of comparisons: " << num << endl;

		if (smallest != i) {
			swap(list[i], list[smallest]);
		}

		for (int k = 0; k < 10; k++) {
			cout << list[k] << ", ";
		}
		cout << list[10] << endl;
		cout << endl;
	}

	

	return 0;
}