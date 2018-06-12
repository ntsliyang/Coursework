#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double degree;
	cout << "Enter the angle theta in degrees: ";
	cin >> degree;
	for (int i = 0; i < 30; i++)
	{
		int y = tan((M_PI / 180.0) * degree) * i;
		if (y >= 20 && y <= 30)
		{
			y = 20;
		}
			
		for (int i = 0; i < y; i++) {
				cout << '*';
		}
		cout << endl;
	}

	return 0;
}