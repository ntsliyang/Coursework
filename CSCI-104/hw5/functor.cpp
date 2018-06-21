#include "functor.h"
#include <functional>
using namespace std;

template <class Comparator>
void DoStringCompare(const std::string &s1, const std::string &s2, Comparator comp)
{
	std::cout << comp(s1, s2) << std::endl; // calls comp.operator()(s1,s2);
}

int NumStrComp::digitSum(const std::string &str)
{
	int sum = 0;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			sum += str[i] - 'a' + 10;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			sum += str[i] - 'A' + 10;
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			sum += str[i] - '0';
		}
	}
	return sum;
}
bool NumStrComp::operator()(const std::string &lhs, const std::string &rhs)
{
	int sum1 = digitSum(lhs);
	int sum2 = digitSum(rhs);
	return (sum1 < sum2);
}

bool AlphaStrComp::operator()(const std::string &lhs, const std::string &rhs)
{ // Uses string's built in operator<
	// to do lexicographic (alphabetical) comparison
	return lhs < rhs;
}

bool LengthStrComp::operator()(const std::string &lhs, const std::string &rhs)
{
	return lhs.size() < rhs.size();
}
