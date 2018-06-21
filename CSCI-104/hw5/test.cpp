#include "functor.h"
#include "qsort.h"
#include "LengthMismatch.h"

using namespace std;
void source(long long remaining, int N, vector<int> &turkeys, vector<int> &potatoes)
{
	srand(time(0));
	for (int _ = 0; _ < N; _++)
	{
		int temp = rand() % remaining;
		turkeys.push_back(temp);
		potatoes.push_back(remaining - temp);
	}
	random_shuffle(turkeys.begin(), turkeys.end());
	random_shuffle(potatoes.begin(), potatoes.end());
}

void check(vector<pair<int, int>> result)
{
	int sum = result[0].first + result[0].second;
	for (int i = 0; i < result.size(); i++)
	{
		if (result[i].first + result[i].second != sum)
		{
			cout << "ERROR" << endl;
			return;
		}
	}
	cout << "well done" << endl;
	return;
}

void testQsort() {
	vector<double> v;
	v.push_back(5.5);
	v.push_back(6.2);
	v.push_back(9.3);
	v.push_back(11.6);
	v.push_back(13.4);
	v.push_back(7.1);
	v.push_back(8.2);
	v.push_back(10.9);
	v.push_back(12.7);
	v.push_back(14.1);
	QuickSort(v, std::less<double>());
}

int main()
{
	long long remaining;
	int count;
	cin >> remaining >> count;
	vector<int> turkeys;
	vector<int> potatoes;
	source(remaining, count, turkeys, potatoes);

	vector<pair<int, int> > result;
	try
	{
		result = assignPlates(turkeys, potatoes);
	}
	catch (LengthMismatch &l)
	{
		cout << l.what() << endl;
	}

	if (!result.empty())
	{
		check(result);
	}
	else
	{
		cout << "no valid pairing solutions" << endl;
	}
	return 0;
}