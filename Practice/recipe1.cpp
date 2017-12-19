#include <iostream>
#include <string>
#include <fstream>
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
	double factor = atof(argv[1]);
	double amount[101];
	string items[101];
	int count;
	read(argv[2], &count, amount, items);
	
	for (int i = 0; i < count; i++) {
		cout << amount[i] * factor << ' ' << items[i] << endl;
	}
	

	return 0; 
}