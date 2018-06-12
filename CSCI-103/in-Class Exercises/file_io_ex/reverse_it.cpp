#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Please enter the name of the file to read as an argument" << endl;
    return 1;
  }

  char buf[80];
  char buf2[80];
  ifstream ifile("reverseme.txt");

  // Check that the file was opened successfully by checking if
  // myfile is "good".  If it is not, exit.
  if (ifile.fail())
  {
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;
  }

  // Use a single line (function-call) to read in the line of text
  // from the file into the 'buf' array
  ifile.getline(buf, 80);

  // Compute the length of the string entered by the user
  int len = strlen(buf);

  // Reverse the line of text and place it into buf2
  //  Be sure you terminate buf2 with a null terminating character
  for (int i = len - 1; i >= 0; i--) {
    buf2[len - 1 - i] = buf[i];
  }
  buf2[len] = 0;

  // Print the buf2 contents
  cout << buf2 << endl;

  ifile.close();

  return 0;
}
