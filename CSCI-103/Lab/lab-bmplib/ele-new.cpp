#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

int main()
{
	unsigned char image[SIZE][SIZE];
	unsigned char output[SIZE][SIZE];

	readGSBMP("elephant.bmp", image);

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			image[i][j] = image[j][i];
		}
	}

   // at end, display complete image
   // showGSBMP(image);
   
   // save to file
   writeGSBMP("ele-new.bmp", output);
   return 0;
}
