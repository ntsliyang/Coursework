#include <iostream>
#include <algorithm>
using namespace std;

/* Author: Yang Li
 * Program: color_conv
 */

int main()
{
   // Enter your code here
   int red, green, blue;
   double white, cyan, magenta, yellow, black;
   cin >> red >> green >> blue;
   
   white = max (max (red/255.0, green/255.0), blue/255.0);
   cyan = (white - red/255.0)/white;
   magenta = (white - green/255.0)/white;
   yellow = (white - blue/255.0)/white;
   black = 1 - white;

   cout << "cyan: " << cyan << endl;
   cout << "magenta: " << magenta << endl;
   cout << "yellow: " << yellow << endl;
   cout << "black: " << black << endl;
   
   
   return 0;
}
