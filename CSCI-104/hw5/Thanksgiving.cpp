#include "LengthMismatch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "qsort.h"
using namespace std;

std::vector<std::pair<int, int> > assignPlates(std::vector<int> turkeys,
											  std::vector<int> potatoes)
{
	if (turkeys.size() != potatoes.size())
	{
		throw LengthMismatch((int)turkeys.size(), (int)potatoes.size());
	}
	else
	{
		// uses quicksort written in "qsort.h"
		QuickSort(turkeys, std::less<int>());
		QuickSort(potatoes, std::less<int>());
		vector<pair<int, int> > answer;
		// only execute the following if 'size != 0'
		if (turkeys.size() != 0)
		{
			long long sum = turkeys[0] + potatoes[potatoes.size() - 1];
			for (unsigned int i = 0; i < turkeys.size(); i++)
			{
				if (turkeys[i] + potatoes[potatoes.size() - i - 1] == sum)
				{
					answer.push_back(pair<int, int>(turkeys[i], potatoes[potatoes.size() - i - 1]));
				}
				else
				{
					answer.clear();
					break;
				}
			}
		}
		return answer;
	}
}