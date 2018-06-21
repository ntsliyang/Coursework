#include <iostream>

unsigned int calculate1(unsigned int n) {
	if (n <= 1) {
		return n;
	}
	return calculate1(n - 1) + calculate1(n - 2);	
}

unsigned int calculate2(unsigned int n) {
	if (n == 0) {
		return 1;
	}
	return n * calculate2(n - 1);
}

int main(int argc, char* argv[])
{
	unsigned int a = calculate1(10) - 13;
	unsigned int b = calculate2(8) + 0x629be;
	unsigned int meaningOfLife = ~(((a + b - 0x629b1) >> 8 ) ^ 0x88) & 0x3f;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << meaningOfLife << std::endl;

	return 0;
}