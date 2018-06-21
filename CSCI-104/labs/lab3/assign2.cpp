#include <algorithm>
#include <cmath>
#include <iostream>

int main(int argc, char* argv[])
{
	double temp1 = 1;
	double temp2 = 2;
	double temp3 = 1;

	double a = 0;
	double b = 0;

	b = (temp2 * temp2) - (4 * temp1 * temp3);
	if (b < 0)
	{
		std::cout << "No real root for " << temp1 << "x^2+";
		std::cout << temp2 << "x+" << temp3 << std::endl;
	}
	else
	{
		a = (-temp2 + std::sqrt(b)) / (2 * temp1);
		std::cout << "One of the roots for " << temp1 << "x^2+";
		std::cout << temp2 << "x+" << temp3;
		std::cout << " is " << a << std::endl;
	}

	temp1 = 1;
	temp2 = 4;
	temp3 = 29;

	b = (temp2 * temp2) - (4 * temp1 * temp3);
	if (b < 0)
	{
		std::cout << "No real root for " << temp1 << "x^2+";
		std::cout << temp2 << "x+" << temp3 << std::endl;
	}
	else
	{
		a = (-temp2 + std::sqrt(b)) / (2 * temp1);
		std::cout << "One of the roots for " << temp1 << "x^2+";
		std::cout << temp2 << "x+" << temp3;
		std::cout << " is " << a << std::endl;
	}

	temp1 = 1;
	temp2 = 84;
	temp3 = 1764;

	b = (temp2 * temp2) - (4 * temp1 * temp3);
	if (b < 0)
	{
		std::cout << "No real root for " << temp1 << "x^2+";
		std::cout << temp2 << "x+" << temp3 << std::endl;
	}
	else
	{
		a = (-temp2 + std::sqrt(b)) / (2 * temp1);
		std::cout << "One of the roots for " << temp1 << "x^2+";
		std::cout << temp2 << "x+" << temp3;
		std::cout << " is " << a << std::endl;
	}


	return 0;
}