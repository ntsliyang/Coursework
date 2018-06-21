#include <iostream>

int main(int argc, char* argv[])
{
	int sum = 0;
	for(int i = 0; i < 10; i++)
	{
		sum += i;
	}
	std::cout << "Sum of the first 10 numbers: " << sum << std::endl;

	sum = 0;
	for(int i = 0; i < 100; i++)
	{
		sum += i;
	}
	std::cout << "Sum of the first 100 numbers: " << sum << std::endl;

	sum = 0;
	for(int i = 0; i < 1000; i++)
	{
		sum += i;
	}
	std::cout << "Sum of the first 1000 numbers: " << sum << std::endl;

	return 0;
}