#include <iostream>
#include <fstream>
using namespace std;

void selectionSort(int*, int);

int main(int argc, char *argv[])
{
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

	selectionSort(data, count);

	for (int i = 0; i < count; i++)
	{
		cout << data[i] << ' ';
	}
	cout << endl;
	return 0;
}

void selectionSort(int* data, int len) {
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
		selectionSort(data, len-1);
	}
}