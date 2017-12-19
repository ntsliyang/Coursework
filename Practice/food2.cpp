#include <iostream>
#include <string>
using namespace std;

string best(string* countries, int* scores, int num) {
	int max_idx = 0;
	int max = scores[0];
	int i;
	for (i = 0; i < num; i++) {
		if (max < scores[i]) {
			max = scores[i];
			max_idx = i;
		}
	}

	scores[max_idx] = 0;
	return countries[max_idx];
}

int main (int argc, char* argv[]) {
	int n;
	cin >> n;
	string* countries = new string [n];
	int* scores = new int [n];
	for (int i = 0; i < n; i++) {
		cin >> countries[i] >> scores[i];
	}

	for (int i = 1; i <= atoi(argv[1]); i++) {
		cout << "Rank " << i << ": " << best(countries, scores, n) << endl;
	}

	
	delete [] countries;
	delete [] scores;

	return 0;
}