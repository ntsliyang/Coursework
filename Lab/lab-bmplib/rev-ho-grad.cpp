#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

int main()
{
	unsigned char image[SIZE][SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = 255;
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = (i + j) / 2;
		}
	}
	showGSBMP(image);

	// at end, display complete image
	// showGSBMP(image);

	// save to file
	writeGSBMP("rev-ho-grad.bmp", image);
	return 0;
}
