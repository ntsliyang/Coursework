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
			int tmp = 0;
			for (int j = 0; j < k; j++)
			{
				int temp = rand() % N;
				if (pop[temp] == false){
					pop[temp] = true;
					tmp++;
				}
			}
			k += tmp;
			night++;
			// compute the number of nights
		}

		max_nights = max(max_nights, night);
		min_nights = min(min_nights, night);
		avg_nights += night;
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