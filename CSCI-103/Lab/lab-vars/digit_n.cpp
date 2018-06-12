#include <iostream>
using namespace std;
int main () {
	int x; 
	cout << "Enter an integer of any size: ";
	cin >> x;
	cout << x%10 << endl;
	while (x/=10) {
		int y = x%10;
		cout << y << endl;
	}

	return 0;
}