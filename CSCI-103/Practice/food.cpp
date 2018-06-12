#include <iostream>
#include <iterator>
#include <string>
using namespace std;

int score(int* ratings, int b) {
	int max = ratings[0];
	int min = ratings[0];
	for (int i = 0; i < b; i++) {
		if (max < ratings[i]) {
			max = ratings[i];
		}

		if (min > ratings[i]) {
			min = ratings[i];
		}
	}

	int total = 0;
	for (int i = 0; i < b; i++) {
		total += ratings[i];
	}
	if (b - 2 > 0) {
		int final = static_cast<int> (0.5 + (total-max-min) / (b - 2.0));
		return final;
	}
	return 0;


}

int main(int argc, char* argv[]) {
	int a, b;
	cin >> a >> b;
	int** rat = new int* [a];
	for (int i = 0; i < a; i++) {
		rat[i] = new int [b];
	}
	
	string* count = new string [a];
	int* result = new int [a];
	for (int i = 0; i < a; i++) {
		cin >> count[i];
		for (int j = 0; j < b; j++) {
			cin >> rat[i][j];
		}
	}

	for (int i = 0; i < a; i++) {
		result[i] = score(rat[i], b);
	}

	cout << a << endl;
	for (int i = 0; i < a; i++) {
		cout << count[i] << ' ' << result[i] << endl;
	}

	for (int i = 0; i < a; i++) {
		delete [] rat[i];
	}
	delete [] rat;

	delete [] count;
	delete [] result;

	return 0;
}