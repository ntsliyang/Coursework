/*********************************************************************
 File:     chromakey.cpp

 Author:   Yang Li

 Email address: yli546@usc.edu

 Usage: program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp

 Notes:
 This program performs the chroma key operation on an input 
 using two different methods.

 Method 1 Utilize a user-defined distance threshold from the
          chromakey value as a discriminator

 Method 2 Devise a method that to determine the chromakey mask
          that doesn't require a user-input threshold

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "bmplib.h"
#include <algorithm>

using namespace std;
// Prototypes
// IMPORTANT: you must exactly use these input types, function names, and
// return types. Otherwise the grader can't test them.
void method1(unsigned char inImage[][SIZE][RGB],
             bool mask[][SIZE],
             double threshold);

void method2(unsigned char inImage[][SIZE][RGB],
             bool mask[][SIZE]);

void replace(bool mask[][SIZE],
             unsigned char inImage[][SIZE][RGB],
             unsigned char bgImage[][SIZE][RGB],
             unsigned char outImage[][SIZE][RGB]);

/*
top-left pixel: (69, 140, 20);
colbert's arm: (235, 151, 105);
colbert's vest: (23, 22, 20);
colbert's shirt: (255, 216, 243);

distance from chromakey to colbert's arm: (166, 11, 85);
distance from chromakey to colbert's vest: (46, 118, 0);
distance from chromakey to colbert's shirt: (186, 76, 223);
*/

int main(int argc, char *argv[])
{
  // Image data array
  // Note:  DON'T use the static keyword except where we expressly say so.
  //        It puts the large array in a separate, fixed, area of memory.
  //        It is bad practice. But useful until we have dynamic allocation.
  static unsigned char inputImage[SIZE][SIZE][RGB];
  static unsigned char bgrndImage[SIZE][SIZE][RGB];
  static unsigned char outputImage[SIZE][SIZE][RGB];
  static bool chromaMask[SIZE][SIZE];

  readRGBBMP("colbert_gs.bmp", inputImage);
  readRGBBMP("campus1.bmp", bgrndImage);

  double threshold;

  if (argc < 6)
  {
    cerr << "usage: program_name in.bmp background.bmp dist_threshold "
         << "out1.bmp out2.bmp" << endl;
    return 0;
  }

  if (readRGBBMP(argv[1], inputImage))
  {
    cerr << "Error reading file: " << argv[1] << endl;
    return 1;
  }

  if (readRGBBMP(argv[2], bgrndImage))
  {
    cout << "Error reading file: " << argv[2] << endl;
    return 1;
  }

  // Write code to convert the threshold (argv[3])
  //  from string format to a double and assign the 'threshold'
  threshold = atof(argv[3]);

  // Call Method 1 Function
  method1(inputImage, chromaMask, threshold);

  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage))
  {
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }

  writeRGBBMP("colbert1.bmp", outputImage);
  // Call Method 2 Function
  method2(inputImage, chromaMask);

  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[5]
  if (writeRGBBMP(argv[5], outputImage))
  {
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }

  writeRGBBMP("colbert2.bmp", outputImage);
  return 0;
}

// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method1(unsigned char inImage[][SIZE][RGB],
             bool mask[][SIZE],
             double threshold)
{

  double distance;

  int chroma_red_i = 0;
  int chroma_green_i = 0;
  int chroma_blue_i = 0;

  // Use the R,G,B values of first 4 rows
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      chroma_red_i += inImage[i][j][0];
      chroma_green_i += inImage[i][j][1];
      chroma_blue_i += inImage[i][j][2];
    }
  }

  int chroma_red_j = 0;
  int chroma_green_j = 0;
  int chroma_blue_j = 0;

  // Use the R,G,B values of first 4 columns
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      chroma_red_j += inImage[i][j][0];
      chroma_green_j += inImage[i][j][1];
      chroma_blue_j += inImage[i][j][2];
    }
  }

  // add them up and calculate the average
  // later in the distance formula
  int chroma_red = chroma_red_i + chroma_red_j;
  int chroma_green = chroma_green_i + chroma_green_j;
  int chroma_blue = chroma_blue_i + chroma_blue_j;

  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      // distance is calculated using the distance formula
      distance = sqrt(pow((inImage[i][j][0] - chroma_red / (8 * SIZE)), 2) 
      + pow((inImage[i][j][1] - chroma_green / (8 * SIZE)), 2) 
      + pow((inImage[i][j][2] - chroma_blue / (8 * SIZE)), 2));
      if (distance <= threshold)
      {
        mask[i][j] = true; //background image
      }
      else
      {
        mask[i][j] = false; //foreground image
      }
    }
  }
}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method2(unsigned char inImage[][SIZE][RGB],
             bool mask[][SIZE])

{
  int num_red = 0;
  int num_green = 0;
  int num_blue = 0;

  // calculate the number of times of each color
  // that appears in the image
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      for (int k = 0; k < RGB; k++)
      {
        if ((inImage[i][j][1] > inImage[i][j][0]) &&
            (inImage[i][j][1] > inImage[i][j][2]))
        {
          num_green++;
        }
        else if ((inImage[i][j][0] > inImage[i][j][1]) &&
                 (inImage[i][j][0] > inImage[i][j][2]))
        {
          num_red++;
        }
        else if ((inImage[i][j][2] > inImage[i][j][0]) &&
                 (inImage[i][j][2] > inImage[i][j][1]))
        {
          num_blue++;
        }
      }
    }
  }

  // If the number of one particular is larger than the number 
  // of each color, it could be processed individually to 
  // differentiate the background and foreground

  double rb_factor = 1.3; 
  int g_threshold = 22;

  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (num_red > num_blue && num_red > num_green)
      {
        if (inImage[i][j][0] <= rb_factor * inImage[i][j][1])
        {
          mask[i][j] = true;
        }
        else
        {
          mask[i][j] = false;
        }
      }
      else if (num_green > num_red && num_green > num_red)
      {
        if (inImage[i][j][1] >= g_threshold + inImage[i][j][0])
        {
          mask[i][j] = true;
        }
        else
        {
          mask[i][j] = false;
        }
      }
      else if (num_blue > num_red && num_blue > num_green)
      {
        if (inImage[i][j][2] >= rb_factor * inImage[i][j][0])
        {
          mask[i][j] = true;
        }
        else
        {
          mask[i][j] = false;
        }
      }
    }
  }
}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
             unsigned char inImage[SIZE][SIZE][RGB],
             unsigned char bgImage[SIZE][SIZE][RGB],
             unsigned char outImage[SIZE][SIZE][RGB])
{
  // Create the output image using the mask to determine
  //  whether to use the pixel from the Input or Background image
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      for (int k = 0; k < RGB; k++)
      {
        if (mask[i][j] == true)
        {
          outImage[i][j][k] = bgImage[i][j][k];
        }
        else
        {
          outImage[i][j][k] = inImage[i][j][k];
        }
      }
    }
  }
}