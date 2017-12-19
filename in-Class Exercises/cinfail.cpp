#include <iostream>
using namespace std;

int main()
{
	int x;
	cout << "Enter an int: " << endl;
	cin >> x;

/*	if (cin.fail()) {
		cout << "Bad!" << endl;
	}
	else {
		cout << "Good, you entered:" << x << endl;		
*/	}
	while(cin.fail()) {
		cin.clear(); // turn off fail flag
		cin.ignore(256, '\n'); // clear inputs 
		cout << "Error: I said enter an int!" << ' ';
		cin >> x;	
	}

	cout << "Good you entered: " << x << endl;
	return 0;
}