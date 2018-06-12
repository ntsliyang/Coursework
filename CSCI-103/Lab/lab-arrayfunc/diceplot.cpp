/********************************************************
 * CS 103 Lab 4 diceplot
 * Name: Yang Li
 * USC email: yli546@usc.edu
 ********************************************************/

#include <iostream>
using namespace std;
const int n = 1234567;
const int numSide = 6, numDice = 4;
int arr[n];

int roll()
{
	int sum = 0;
	for (int i = 0; i < numDice; i++)
	{
		sum += rand() % numSide + 1;
	}
	return sum;
}

void printHistogram(int counts[])
{
	for (int j = 0; j < numSide * numDice - numDice + 1; j++)
	{
		cout << j + numDice << ':';
		// print sequential labelled lines from (numDice) to (numSide * numDice - numDice + 1)
		for (int k = 0; k < counts[j]; k++)
		{
			cout << 'X';
		}
		// print 'X' symbols on that line as is indicated in the appropriate element of the array
		cout << endl;
	}
}

int main()
{
	srand(time(0));
	int num;
	cin >> num;
	int testCounts[numSide * numDice - numDice + 1]; // (numSide * numDice - numDice + 1) options of sum of (numDice) dice
	for (int i = 0; i < num; i++)
	{
		roll();
		for (int h = 0; h < num; h++)
		{
			arr[h] = roll();
		}
	}

	for (int k = 0; k < numSide * numDice - numDice + 1; k++)
	{
		testCounts[k] = 0;
		for (int h = 0; h < num; h++)
		{
			if (k + numDice == arr[h])
			{
				testCounts[k]++;
			}
		}
	}

	printHistogram(testCounts); // call method
	return 0;
}