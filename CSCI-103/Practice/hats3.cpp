#include <iostream>
using namespace std;
int main()
{
	int list[] = {8, 9, 2, 1, 4, 7, 5, 3, 6};
	int temp[1000];
	int cycle[10];
	for (int i = 1; i <= 9; i++)
	{
		int num = 1;
		if (i == list[i])
		{
			cout << 1 << endl;
			return 0;
		}
		bool flag = true;
		int j = i;
		while (flag == true)
		{
			temp[num] = j;
			temp[++num] = list[j];
			j = list[j];
			for (int a = 1; a <= 1000; a++)
			{
				for (int b = 1; b <= 1000; b++)
				{
					if (temp[a] == temp[b] && a != b)
					{
						flag = false;
					}
				}
			}
		}
		cycle[i] = num;
	}

	for (int i = 1; i <= 9; i++)
	{
		cout << cycle[i] << endl;
	}
	return 0;
}