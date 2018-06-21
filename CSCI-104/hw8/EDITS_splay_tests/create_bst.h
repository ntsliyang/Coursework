// Header that implements functions for creating BSTs.

#include <set>
#include <limits>
#include <random>
#include <algorithm>

#include "user_bst_headers.h"

#ifndef CREATE_BST_H
#define CREATE_BST_H

/* Generates a set of unique random integers of the given length,
	with the given seed.

	Modified from Smith Test Case Co's HW5 test code.
*/
inline std::set<int> makeRandomIntSet(size_t count, int seed)
{
	// set up random number generator
	std::default_random_engine randEngine;
	randEngine.seed(seed);

	// make numbers in [-count, 3*count]
	std::uniform_int_distribution<int> distributor(-1 * ((int)count), ((int)count) * 4);

	// keep adding numbers until we have enough.
	// We can't use a for-loop because some numbers are duplicates and won't count.
	std::set<int> randomSet;
	do
	{
		randomSet.insert(distributor(randEngine));
	}
	while(randomSet.size() < count);

	return randomSet;
}

/* Fills the given bst with one node for each item in the set.
   The key and value of the node are both set to the item's value.

   This way, keys in the tree will be ordered the same way
   they are in the set, and it will be easy to check that
   the value corresponding to a key was correctly stored.

   So that the tree will be roughly balanced, values will
   be inserted in *random* order with the given seed.

*/
template<typename Key>
void fillTree(BinarySearchTree<Key, Key> & tree, std::set<Key> const & dataSet, int randomSeed)
{
	// set up random number generator
	std::default_random_engine randEngine;
	randEngine.seed(randomSeed);

	std::vector<Key> setElements(dataSet.begin(), dataSet.end());
	std::shuffle(setElements.begin(), setElements.end(), randEngine);

	for(size_t index = 0; index < setElements.size(); ++index)
	{
		tree.insert(std::make_pair(setElements[index], setElements[index]));
	}
}

#endif
