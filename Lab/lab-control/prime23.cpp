#include <iostream>
using namespace std;
int main () {
	int x, Twos = 0, Threes = 0;
	cin >> x;
	
	while (x%2 == 0) {
		Twos++;
		x /=2;
	}
	while (x%3 == 0) {
		Threes++;
		x /=3;
	}
	
	if (x == 1)
	{
		cout << "Twos=" << Twos << ' ' << "Threes=" << Threes << endl;
	}
	else {cout << "No" << endl;}

}