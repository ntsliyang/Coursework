#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
using namespace std;

double meltage(double currSnow, int temp, int salt) {
	double fac1 = 1.0000 + currSnow;
	double fac2 = (temp - 32 + 2 * salt) / 18.0;
	return min(currSnow, pow(fac1, fac2));
}

void printArray(double** arr, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf(".3f", arr[i][j]);
		}
		cout << endl;
	}
}
 
int main(int argc, char* argv[]) {
	int n = 0;
	double snow[10000];
	int temp[10000];
	while (!cin.fail()) {
		cin >> snow[n] >> temp[n];
		n++;
	}
	n -= 1;
	int num = argc - 1;
	double** arr = new double* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new double [num];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < num; j++) {
			if (i - 1 >= 0) {
				arr[i][j] = snow[i] + arr[i-1][j] - meltage(snow[i] + arr[i-1][j], temp[i], atoi(argv[j + 1])); 
			}
			else {
				arr[i][j] = snow[i] - meltage(snow[i], temp[i], atoi(argv[j + 1]));
			}
		}
	}

	printArray(arr, n, num);

	for (int i = 0; i < n; i++) {
		delete [] arr[i];
	}
	delete [] arr;

	return 0;
}