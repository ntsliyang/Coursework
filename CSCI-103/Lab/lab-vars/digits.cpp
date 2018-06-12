#include <iostream>
using namespace std;

/* Author: Yang Li
 * Program: digits
 */

int main () {
	int x, d1, d2, d3; 
	cout << "Enter an integer between 0 and 999: ";
	cin >> x;
	d1 = x%10;
	d2 = (x/10)%10;
	d3 = x/100;
	
	cout << "1's digit is " << d1 << endl;
	cout << "10's digit is " << d2 << endl;
	cout << "100's digit is " << d3 << endl;
	
	return 0;
}