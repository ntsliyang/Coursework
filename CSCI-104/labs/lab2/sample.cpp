#include <iostream>
#include <stdlib.h>

using namespace std;

int TheTruth()
{
	void* buffer;

	// Allocate memory for buffer and return the pointer to that memory.
	buffer = malloc(1 << 31);

	// Place the meaning of life into memory
	*(int*)buffer = ( (1 << 5) + 10 ) ^ 0x04 ^ 0x04;

	// Read from that area in memory, and return life's meaning!
	return *(int*)buffer;
}

int main()
{	
	cout << "What is the meaning";
	cout << " of life?" << endl;
	cout << TheTruth () << endl;
	return 0;
}
