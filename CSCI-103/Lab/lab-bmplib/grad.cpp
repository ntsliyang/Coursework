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
		for (int j = 0; j < i + 1; j++) {
			image[j][i + 1 - j] = i;
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = i; j >= 0; j--) {
			image[SIZE-1-j][SIZE - (i - j)-1] = i;
		}
	}

	/* diagonal line defined as d;
   i = 0; j = 1; [0, 0];
   i = 1; j = 2; [0, 1], [1, 0];
   i = 2; j = 3; [0, 2], [1, 1], [2, 0];
   ......
   i = n, j = n + 1, 

   image[SIZE][SIZE] = 0;
   image[SIZE - 1][SIZE] = 1; image[SIZE][SIZE - 1] = 1;
   SIZE - 2, SIZE; SIZE - 1, SIZE - 1, SIZE, SIZE - 2 = 2;

   i = 255; 

   */
   // at end, display complete image
   // showGSBMP(image);
   
   // save to file
   writeGSBMP("grad.bmp", image);
   return 0;
}
