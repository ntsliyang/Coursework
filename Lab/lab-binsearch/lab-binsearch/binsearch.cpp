#include <iostream>
#include <fstream>

using namespace std;

void sort(int *, int);
int binsearch(int, int *, int, int);

int main(int argc, char *argv[])
{
  int target;
  if (argc < 2)
  {
    cout << "Provide a filename of the data to be searched" << endl;
    return 1;
  }
  ifstream datfile(argv[1], ios::in);
  if (datfile.fail())
  {
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;
  }
  int count = 0;
  // Count how many integers are in the file
  while (!datfile.fail())
  {
    int temp;
    datfile >> temp;
    if (!datfile.fail())
    {
      count++;
    }
  }
  // When we reach the end of the file, the EOF flag is set
  // To be able to read through the file again we need to clear that flag
  datfile.clear();
  //  We also need to set our internal position in the file back to 0
  datfile.seekg(0, ios::beg);

  // Now allocate an array to store the file data and read in the data
  int *data = new int[count];
  for (int i = 0; i < count; i++)
  {
    datfile >> data[i];
  }

  datfile.close();

  cout << "Read " << count << " integers from the data file.\n"
       << endl;
  cout << "Enter the target positive integer to search for: ";
  cin >> target;

  // sort(data, count);
  sort(data, count);
  for (int i = 0; i < count; i++) {
    cout << data[i] << ' ';
  }
  cout << endl;
  // Call binary search
  int retval = binsearch(target, data, 0, count);

  // Interpret and print the results
  if (retval == -1)
  {
    cout << target << " does not appear in the data." << endl;
  }
  else
  {
    cout << target << " appears at index " << retval << " in the data." << endl;
  }

  // Deallocate the data array
  delete[] data;
  return 0;
}

// Returns the index in the data array where target is located
//  or -1 if the target value is not in the data
int binsearch(int target, int *data, int start, int end)
{
  int mid = (start + end) / 2;
  
  if (start >= end)
  {
    return -1;
  }

  if (data[mid] == target)
  {
    return mid;
  }
  else {
    if (target < data[mid])
    {
      return binsearch(target, data, start, mid);
    }
    else
    {
      return binsearch(target, data, mid + 1, end);
    }
  }

 



  return 0;
}

// implements a selection sort algorithm to sort
//  the integer values in the 'data' array of size 'len'
// You aren't allowed to change the prototype of this function
void sort(int *data, int len)
{
  // iterative implementation
/*for (int i = 0; i < len - 1; i++)
  {
    int smallest = i;
    int num = 0;
    for (int j = i + 1; j < len; j++)
    {
      if (data[j] < data[smallest])
      {
        smallest = j;
        num++;
      }

      else
      {
        num++;
      }
    }

    if (smallest != i)
    {
      swap(data[i], data[smallest]);
    }
  }
*/
  // recursive implementation
	int max = 0, i;
	
	for (i = 0; i < len; i++) {
		if (data[max] < data[i]) {
			max = i;
		}
	}

	if (data[len-1] != data[max]) {
		swap(data[max], data[len-1]);
	}

	if (len > 1) {
		sort(data, len-1);
	}
}