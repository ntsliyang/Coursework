#include <iostream>
#include <string>

template <class Comparator>
void DoStringCompare(const std::string &s1, const std::string &s2, Comparator comp);

struct NumStrComp
{
	int digitSum(const std::string &str);
	bool operator()(const std::string &lhs, const std::string &rhs);
};

struct AlphaStrComp
{
	bool operator()(const std::string &lhs, const std::string &rhs);
};

struct LengthStrComp
{
	bool operator()(const std::string &lhs, const std::string &rhs);
};