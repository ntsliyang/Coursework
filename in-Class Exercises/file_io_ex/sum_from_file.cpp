#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  ifstream ifile(argv[1]);
  int x, y;

  if (ifile.fail()) {
    cout << "Couldn't open file" << endl;
    return 1;
  }

  ifile >> x >> y;

  if (ifile.fail()) {
    cout << "Didn't enter an int or double" << endl;
    ifile.close();
    return 1;
  }

  cout << "X=" << x << " and Y=" << y << endl;

  ofstream ofile("output_num2.txt");

  ofile << "X=" << x << " and Y=" << y << endl;
  ofile << "The sum from file is " << x + y << endl;

  cout << "The sum from file is " << x + y << endl;

  ifile.close();
  ofile.close();

  return 0;
}
