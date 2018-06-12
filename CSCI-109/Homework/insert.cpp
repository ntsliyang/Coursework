#include <iostream>
using namespace std;
int main () {
	int list[] = {2, 3, 4, 8, 6, 9, 11, 13, 16, 15, 21};

	for (int i = 0; i < 11; i++) {
		while (i < 11) {
			int j = i;
			int num = 0;
			while (j > 0) {
				if (list[j - 1] > list[j]) {
					swap(list[j], list[j - 1]);
					cout << "Compare " << list[j] << " to " << list[j - 1] << "; ";
					cout << list[j - 1] << " < " << list[j] << ", ";
					cout << "so the two values are swapped." << endl;
					j = j - 1;
					num++;
				}

				else {
					cout << "Compare " << list[j] << " to " << list[j - 1] << "; ";
					cout << list[j - 1] << " < " << list[j] << ", ";
					cout << "so there is no swap." << endl;
					num++;
					break;
				}
			}

			cout << "Number of comparisons: " << num;
			cout << endl;

			for (int k = 0; k < 10; k++) {
				cout << list[k] << ", ";
			}
			cout << list[10] << endl;
			cout << endl;
			i++;
		}

	}

	return 0;
}