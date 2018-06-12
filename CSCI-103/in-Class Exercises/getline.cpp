#include <iostream>
using namespace std;
int main()
{
	char mytext[80];
	cout << "Enter your full name" << endl;
	cin.getline(mytext, 80);
	int last = 0;
	for (int i = 0; i < 80; i++)
	{
		if (mytext[i] == ' ')
		{
			last = i;
			break;
		}
	}
	cout << "Last name starts at index: ";
	cout << last << endl;
	return 0;
}