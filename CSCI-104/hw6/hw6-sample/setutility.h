#ifndef SETUTILITY_H
#define SETUTILITY_H
#include <set>
#include <string>
#include <map>
#include <vector>

template<typename T>
std::set<T> intersection(std::set<T> &s1, std::set<T> &s2)
{
	std::set<T> temp;
	for (auto i = s1.begin(); i != s1.end(); i++)
	{
		if (s2.find(*i) != s2.end())
		{
			temp.insert((*i));
		}
	}
	return temp;
} // find the intersection of two sets of strings
// and return the intersected set

template <typename T>
std::set<T> intersectWebPage(std::map<T, std::set<T> > &m)
{
	if (m.size() == 1)
	{
		return m.begin()->second;
	} // if there is only one set, return this set
	else
	{
		std::set<T> temp = m.begin()->second;
		for (auto i = m.begin(); i != m.end(); i++)
		{
			temp = intersection(temp, i->second);
		}
		return temp;
	}
}

template <typename T>
std::set<T> setunion(std::set<T> &s1, std::set<T> &s2)
{
	std::set<T> temp = s1;
	for (auto i = s2.begin(); i != s2.end(); i++)
	{
		temp.insert(*i);
	}
	return temp;
} // find the union of two sets of strings, and return the union set

template <typename T>
std::set<T> unionWebPage(std::map<T, std::set<T> > &m)
{
	if (m.size() == 1)
	{
		return m.begin()->second;
	} // if there is only one set, return this set
	else
	{
		std::set<T> temp = m.begin()->second;
		for (auto i = m.begin(); i != m.end(); i++)
		{
			temp = setunion(temp, i->second);
		}
		return temp;
	}
}

#endif