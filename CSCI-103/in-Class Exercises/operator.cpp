#include <iostream>
#include <fstream>
using namespace std;
int main () {
/*	ifstream ifile("data.txt");
	char c = ifile.get();
	cout << c << endl;
	char C = ifile.get();
	cout << C << endl;
	char D = ifile.peek();
	cout << D << endl;
	ifile.close();
*/

	int size;
	char c;
	ifstream is("data.txt");
	is.seekg(0, ios_base::end);
	size = is.tellg();
	cout << "File size (bytes) " << size << endl;
	
	is.seekg(1, ios_base::beg);
	cout << "2nd byte in file is ";
	is >> c;
	cout << c << endl;

	is.seekg(-2, ios_base::cur);
	cout << "1st byte in file is ";
	is >> c;

	cout << c << endl;
	is.close();
	return 0;
}