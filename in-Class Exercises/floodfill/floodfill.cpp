#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

unsigned char image[SIZE][SIZE];

// Prototypes
void print_menu();
void draw_rectangle(int ulr, int ulc, int h, int w);
void draw_ellipse(int cr, int cc, int a, int b);
void flood_fill(int cr, int cc);

void print_menu()
{
  cout << "\nTo draw a rectangle, enter: 0 upper-left-row upper-left-col height width" << endl;
  cout << "To draw an ellipse, enter: 1 center_pt_row center_pt_col major-len minor-len" << endl;
  cout << "To fill an area with black, enter: 2 pt_row pt_col" << endl;
  cout << "To save your drawing as \"output.bmp\" and quit, enter: 3" << endl;
  cout << "\nEnter choice: " << endl;
}
int main()
{
  int choice, ulr, ulc, h, w, cr, cc, a, b;
  choice = -1;
  // initialize the image to all white pixels
  for(int i=0; i < SIZE; i++){
    for(int j=0; j < SIZE; j++){
      image[i][j] = 255;
    }
  }

  while(choice != 3){
    print_menu();
    cin >> choice;
    if(choice == 0){
      cin >> ulr >> ulc >> h >> w;
      draw_rectangle(ulr, ulc, h, w);
    }
    else if(choice == 1){
      cin >> cr >> cc >> a >> b;
      draw_ellipse(cr, cc, a, b);
    }
    else if(choice == 2){
      cin >> cr >> cc;
      flood_fill(cr, cc);
    }
  }
  writeGSBMP("output.bmp", image);
  return 0;
}

void draw_rectangle(int ulr, int ulc, int h, int w)
{
  for(int r=ulr; r < ulr+h; r++){
    image[r][ulc] = 0;
    image[r][ulc+w] = 0;
  }
  for(int c=ulc; c < ulc+w; c++){
    image[ulr][c] = 0;
    image[ulr+h][c] = 0;
  }
}

void draw_ellipse(int cr, int cc, int a, int b)
{
  double r = a/2;
  for(double theta=0.0; theta < 2*M_PI; theta += .01){
    int x = r*cos(theta);
    int y = (b/2)*sin(theta);
    x += cc;
    y += cr;
    image[y][x] = 0;
  }
}

void flood_fill(int r, int c)
{
  // base case 1 - black pixel
  if (image[r][c] == 0) {
    return;
  }
  // base case 2 - out of bounds
  else if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
    return;
  }
  else {
    image[r][c] = 0;
    flood_fill(r-1, c); // north
    flood_fill(r, c-1); // west 
    flood_fill(r+1, c); // south
    flood_fill(r, c+1); // east
  }
}
