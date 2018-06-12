/********************************************************
 * CS 103 Zombie-pocalypse PA
 * Name: Yang Li
 * USC email: yli546@usc.edu
 * Description:
 * The program first sets k number of population as zombies,
 * and (N - k) number of population as humans, by starting
 * a for loop that simulates m times of zombie-pocalypse.
 * Then, starting a while loop that simulates one-night 
 * situation, the program gives a for loop by computing the
 * number of nights. Finally, the program computes max nights, 
 * min nights, and average nights by simple algorithms. 
 ********************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

const int MAXPOP = 100000;

int main()
{
	// Array with enough entries for the maximum population size possible.
	bool pop[MAXPOP];

	// Your code here
	int N, k, M, seed;
	cout << "Enter the following: N k M seed" << endl;
	cin >> N >> k >> M >> seed;

	srand(seed);
	int a = k;
	int night;

	int max_nights = -1;
	int min_nights = 10000;
	int nights[123456];
	double avg_nights = 0;
	for (int i = 0; i < M; i++)
	{
		k = a;
		night = 0;
		for (int r = 0; r < k; r++)
		{
			pop[r] = true;
		}

		for (int q = k; q < N; q++)
		{
			pop[q] = false;
		}
		// k number of population are zombies, while (N-k) number of population are humans
		while (N > k)
		{
			for (int j = 0; j < k; j++)
			{
				int new_zombie = rand() % N;
				pop[new_zombie] = true;
			}
			// indicate the lastest zombies in the population
			k = 0;
			for (int w = 0; w < N; w++)
			{
				if (pop[w] == true)
				{
					k++;
				}
			}
			night++;
			// compute the number of nights
		}
		nights[i] = night;
	}

	for (int e = 0; e < M; e++)
	{
		avg_nights += nights[e];
		if (nights[e] > max_nights)
		{
			max_nights = nights[e];
		}

		if (nights[e] < min_nights)
		{
			min_nights = nights[e];
		}
	}
	// compute the number of max and min nights
	avg_nights = avg_nights / M;
	cout << "Average nights: " << avg_nights << endl;
	cout << "Max nights: " << max_nights << endl;
	cout << "Min nights: " << min_nights << endl;

	// Print out your average, max, and min number of nights here
	// Be sure to follow the format shown in the assignment writeup.

	return 0;
}