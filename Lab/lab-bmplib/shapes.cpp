#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {

}

// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) {
    // int iters = 0;
    for (double theta=0.0; theta < 2*M_PI; theta += .01) {
       double x = cx*cos(theta);
       double y = cy*sin(theta);
       x += width/2;
       y += height/2;
       image[(int)y][(int)x] = 0;
    } 
}


int main() {
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }

   int a, b, c, d, e;
   cin >> a, b, c, d, e;
   if (a == 0) {
       draw_rectangle(b, c, d, e);
   }
   else if (a == 1) {
       draw_ellipse(b, c, d, e);
   }

   // Main program loop here

   
   
   // Write the resulting image to the .bmp file
   writeGSBMP("output.bmp", image);
   
   return 0;
}

