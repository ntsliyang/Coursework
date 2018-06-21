#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(int argc, char* argv[])
{
	srand (time(NULL));
	int a = rand();
	int b = rand();

	if (a > b)
	{
		int r = a % b;
		int q = a / b;
		std::cout << a << " / " << b;
		std::cout << ": quotient = " << q << " remainder = " << r << std::endl;
	}
	else
	{
		int r = b % a;
		int q = b / a;
		std::cout << b << " / " << a;
		std::cout << ": quotient = " << q << " remainder = " << r << std::endl;
	}
	return 0;
}