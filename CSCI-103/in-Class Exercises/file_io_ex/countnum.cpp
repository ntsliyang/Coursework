#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;
int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    cout << "Please enter the name of the file to read as an argument and the integer to search for" << endl;
    return 1;
  }

  // Declare the ifstream variable here an open the file
  // specified as the 1st command line argument
  ifstream ifile("numlist.txt");
  
  // Read the number of integers specified on the first line
  // into the following variable
  int numInts;
  ifile >> numInts;

  // Dynamically allocate an array of ints of size: numInts
  //  using the 'new' operator
  int* arr = new int[numInts];
  
  // Read the integers on the 2nd line of text in the file into
  //  the array you allocated
  for (int i = 0; i < numInts; i++) {
    ifile >> arr[i];
  }
  
  // Convert the 2nd command line argument to an integer named searchval
  int searchval = atoi(argv[2]);
  
  // Average the last half of the array
  int occurrences = 0;

  for (int i = 0; i < numInts; i++) {
    if (arr[i] == searchval) {
        occurrences++;
      }
  }

  cout << searchval << " appears " << occurrences << " times." << endl;

  // Use delete to deallocate the array you new'ed
  delete [] arr;
  ifile.close();
  
  return 0;
}
