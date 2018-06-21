
#ifndef CREATE_SPLAY_H
#define CREATE_SPLAY_H
#include "check_splay.h"

/* Fills the given splay tree with one node for each item in the set.
   The key and value of the node are both set to the item's value.

   Items will be inserted in random order.

   If any checked insertions fail, will return false.
*/
template<typename Key>
bool fillSplayTreeRandomly(SplayTree<Key, Key> & tree, std::set<Key> const & dataSet, int randomSeed)
{
	// set up random number generator
	std::default_random_engine randEngine;
	randEngine.seed(randomSeed);

	std::vector<Key> setElements(dataSet.begin(), dataSet.end());
	std::shuffle(setElements.begin(), setElements.end(), randEngine);

	for(size_t index = 0; index < setElements.size(); ++index)
	{
		if(!checkedInsert(tree, std::make_pair(setElements[index], setElements[index])))
		{
			return false;
		}
	}

	return true;
}

/* Fills the given splay tree with one node for each item in the set.
   The key and value of the node are both set to the item's value.

   Items will be inserted in sorted least-to-greatest order.

   If any checked insertions fail, will return false.
*/
template<typename Key>
bool fillSplayTreeInOrder(SplayTree<Key, Key> & tree, std::set<Key> const & dataSet)
{
	std::vector<Key> setElements(dataSet.begin(), dataSet.end());

	for(size_t index = 0; index < setElements.size(); ++index)
	{
		if(!checkedInsert(tree, std::make_pair(setElements[index], setElements[index])))
		{
			return false;
		}
	}

	return true;
}

/* Fills the given splay tree with one node for each item in the set.
   The key and value of the node are both set to the item's value.

   Items will be inserted in alternating order: least, then greatest, then second-least, etc..
   This is designed to force the tree to splay as much as possible.

   If any checked insertions fail, will return false.
*/
template<typename Key>
bool fillSplayTreeAlternating(SplayTree<Key, Key> & tree, std::set<Key> const & dataSet)
{

	std::vector<Key> setElements(dataSet.begin(), dataSet.end());

	for(size_t smallerElementIndex = 0; smallerElementIndex < setElements.size()/2; ++smallerElementIndex)
	{

		// insert the element in the first half of the list
		if(!checkedInsert(tree, std::make_pair(setElements.at(smallerElementIndex), setElements.at(smallerElementIndex))))
		{
			return false;
		}

		// then, insert the element in the second half of the list
		size_t largerElementIndex = setElements.size() - 1 - smallerElementIndex;
		if(!checkedInsert(tree, std::make_pair(setElements.at(largerElementIndex), setElements.at(largerElementIndex))))
		{
			return false;
		}

		//std::cout << "Inserted " << setElements.at(smallerElementIndex) << ", then " << setElements.at(largerElementIndex) << std::endl;

	}

	return true;
}

#endif
