#include "splay_tests.h"

#include <gtest/gtest.h>

#include <initializer_list>
#include <utility>

/*
 * Test files that make sure findMin(), findMax(), deleteMinLeaf(), and deleteMaxLeaf() work
 */

TEST(FindMax, Empty)
{
	SplayTree<bool, bool> testTree;
	EXPECT_EQ(testTree.findMax(), testTree.end());
}
TEST(FindMin, Empty)
{
	SplayTree<bool, bool> testTree;
	EXPECT_EQ(testTree.findMin(), testTree.end());
}

TEST(FindMax, OneElement)
{
	SplayTree<short, short> testTree;

	EXPECT_TRUE(checkedInsert(testTree, std::make_pair<short, short>(1, 100)));

	ASSERT_NE(testTree.findMin(), testTree.end());
	EXPECT_EQ(testTree.findMin()->first, 1);
}
TEST(FindMin, OneElement)
{
	SplayTree<short, short> testTree;

	EXPECT_TRUE(checkedInsert(testTree, std::make_pair<short, short>(1, 100)));

	ASSERT_NE(testTree.findMax(), testTree.end());
	EXPECT_EQ(testTree.findMax()->first, 1);
}

TEST(FindMax, Random50x30)
{

	std::default_random_engine seedGenerator;
	seedGenerator.seed(-7);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int counter = 0; counter < 50; ++counter)
	{

		int randomSeed1 = distributor(seedGenerator);
		int randomSeed2 = distributor(seedGenerator);

		std::set<int> randomData = makeRandomIntSet(30, randomSeed1);

		EXPECT_TRUE(fillSplayTreeRandomly(testTree, randomData, randomSeed2));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		int largestElement = *randomData.rbegin();

		ASSERT_NE(testTree.findMax(), testTree.end());
		ASSERT_EQ(testTree.findMax()->first, largestElement);

		testTree.clear();
	}


}
TEST(FindMin, Random50x30)
{

	std::default_random_engine seedGenerator;
	seedGenerator.seed(-8);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int counter = 0; counter < 50; ++counter)
	{

		int randomSeed1 = distributor(seedGenerator);
		int randomSeed2 = distributor(seedGenerator);

		std::set<int> randomData = makeRandomIntSet(30, randomSeed1);

		EXPECT_TRUE(fillSplayTreeRandomly(testTree, randomData, randomSeed2));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		int smallestElement = *randomData.begin();

		ASSERT_NE(testTree.findMin(), testTree.end());
		ASSERT_EQ(testTree.findMin()->first, smallestElement);

		testTree.clear();
	}


}

TEST(DeleteMaxLeaf, Empty)
{
	SplayTree<bool, bool> testTree;
	testTree.deleteMaxLeaf();
	EXPECT_TRUE(verifyBST(testTree, {}));
}
TEST(DeleteMinLeaf, Empty)
{
	SplayTree<bool, bool> testTree;
	testTree.deleteMinLeaf();
	EXPECT_TRUE(verifyBST(testTree, {}));
}

TEST(DeleteMaxLeaf, OneElement)
{
	SplayTree<short, short> testTree;

	EXPECT_TRUE(checkedInsert(testTree, std::make_pair<short, short>(1, 100)));

	testTree.deleteMaxLeaf();

	EXPECT_TRUE(verifyBST(testTree, {}));
}
TEST(DeleteMinLeaf, OneElement)
{
	SplayTree<short, short> testTree;

	EXPECT_TRUE(checkedInsert(testTree, std::make_pair<short, short>(1, 100)));

	testTree.deleteMinLeaf();

	EXPECT_TRUE(verifyBST(testTree, {}));
}

TEST(DeleteMaxLeaf, Random50x30)
{

	std::default_random_engine seedGenerator;
	seedGenerator.seed(-7);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int counter = 0; counter < 50; ++counter)
	{

		int randomSeed1 = distributor(seedGenerator);
		int randomSeed2 = distributor(seedGenerator);

		std::set<int> randomData = makeRandomIntSet(30, randomSeed1);

		EXPECT_TRUE(fillSplayTreeRandomly(testTree, randomData, randomSeed2));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		// find largest element that is also a leaf
		int largestLeafKey;

		for(std::set<int>::reverse_iterator dataRevIter = randomData.rbegin(); dataRevIter != randomData.rend(); ++dataRevIter)
		{
			Node<int, int> * dataNode = testTree.internalFind(*dataRevIter);
			if(dataNode->getLeft() == nullptr && dataNode->getRight() == nullptr)
			{
				//found a leaf node!
				largestLeafKey = *dataRevIter;
				break;
			}
		}

		//prettyPrintBST(testTree);

		// now do the remove
		testTree.deleteMaxLeaf();

		//...and check that it has been removed
		randomData.erase(randomData.find(largestLeafKey));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		testTree.clear();
	}


}
TEST(DeleteMinLeaf, Random50x30)
{

	std::default_random_engine seedGenerator;
	seedGenerator.seed(-7);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int counter = 0; counter < 50; ++counter)
	{

		int randomSeed1 = distributor(seedGenerator);
		int randomSeed2 = distributor(seedGenerator);

		std::set<int> randomData = makeRandomIntSet(30, randomSeed1);

		EXPECT_TRUE(fillSplayTreeRandomly(testTree, randomData, randomSeed2));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		// find smallest element that is also a leaf
		int smallestLeafKey;

		for(std::set<int>::iterator dataRevIter = randomData.begin(); dataRevIter != randomData.end(); ++dataRevIter)
		{
			Node<int, int> * dataNode = testTree.internalFind(*dataRevIter);
			if(dataNode->getLeft() == nullptr && dataNode->getRight() == nullptr)
			{
				//found a leaf node!
				smallestLeafKey = *dataRevIter;
				break;
			}
		}

		//prettyPrintBST(testTree);

		// now do the remove
		testTree.deleteMinLeaf();

		//...and check that it has been removed
		randomData.erase(randomData.find(smallestLeafKey));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		testTree.clear();
	}


}
