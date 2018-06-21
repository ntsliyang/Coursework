#include <iostream> 
#include <fstream>
#include <string>
using namespace std;

void readfile(ifstream&, int);

void readfile(ifstream& myfile, int n) {
	if (n == 0) {
		return;
	}
	else {
		string word;
		myfile >> word;
		readfile(myfile, n -1);
		cout << word << ' ';
	}
}
int main(int argc, char* argv[]) {
	ifstream myfile;
	myfile.open(argv[1]);
	int n;
	myfile >> n;
	readfile(myfile, n);
	cout << endl;
	myfile.close();
	
	return 0;
}