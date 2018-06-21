#include "qsort.h"
#include <iostream>
using namespace std;
int main()
{
	srand(12);
	for (int i = 1; i <= 10000; i++)
	{
		vector<int> v1;
		vector<int> v2;
		int N = rand() % 10;
		for (int j = 1; j <= N; j++)
		{
			int val = rand() % 10;
			v1.push_back(val);
			cout << val << endl;
			v2.push_back(val);
		}
		less<int> c1;
		sort(v1.begin(), v1.end(), c1);
		QuickSort(v2, c1);
		for (int i = 0; i < (int)v1.size(); i++)
		{
			if (v1[i] != v2[i])
			{

				cout << "ERROR" << endl;
				return 0;
			}
		}
		cout << "Test Case #" << i << " Passed." << endl;
	}
	return 0;
}