#pragma once

#include <iostream>
#include <vector>

template <class T>
void swap(T &a, T &b)
{
	T c(a);
	a = b;
	b = c;
}

#define min(x,y) (comp(x,y)?x:y)
#define max(x,y) (!comp(x,y)?x:y)


template <class T, class Comparator>
int findMedian(std::vector<T> &arr, int low, int middle, int high, Comparator comp)
{
	T median = max(min(arr[low],arr[middle]), min(max(arr[low],arr[middle]),arr[high]));
	if (median == arr[low])
		return low;
	else if (median == arr[middle])
		return middle;
	else 
		return high;
	// output the median of three numbers
}

template <class T, class Comparator>
int partition(std::vector<T> &arr, int low, int high, Comparator comp)
{
	int middle = low + (high - low) / 2;
	int mid = findMedian(arr, low, middle, high, comp);
	swap(arr[mid], arr[high]);
	T pivot = arr[high];
	int i = low;
	for (int j = low; j < high; j++)
	{
		if (comp(arr.at(j), pivot))
		{
			swap((arr.at(i)), (arr.at(j)));
			i++;
		}
	}
	swap((arr.at(i)), (arr.at(high)));
	return i;
}

template <class T, class Comparator>
void quickSort(std::vector<T> &arr, int low, int high, Comparator comp)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
           at right place */
		int pi = partition(arr, low, high, comp);
		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1, comp);
		quickSort(arr, pi + 1, high, comp);
	}
}

template <class T, class Comparator>
void QuickSort(std::vector<T> &myArray, Comparator comp)
{
	quickSort(myArray, 0, (int)myArray.size() - 1, comp);
}