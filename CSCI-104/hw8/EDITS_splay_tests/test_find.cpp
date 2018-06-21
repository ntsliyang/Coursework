#include "splay_tests.h"

#include <gtest/gtest.h>

/**
 * File that does some basic and random tests to make sure that the splay tree find function works
 */

TEST(Find, Empty)
{
	SplayTree<double, double> testTree;

	EXPECT_EQ(testTree.find(1.0001), testTree.end());
}

TEST(Find, OneElement)
{
	SplayTree<long, double> testTree;

	EXPECT_TRUE(checkedInsert(testTree, std::make_pair(1L, 2.0)));

	ASSERT_NE(testTree.find(1L), testTree.end());
	EXPECT_EQ(testTree.find(1L)->first, 1L);
}

TEST(Find, SplayFoundPredecessor)
{
	SplayTree<long, double> testTree;

	EXPECT_TRUE(checkedInsert(testTree, std::make_pair(1L, 2.0)));
	EXPECT_TRUE(checkedInsert(testTree, std::make_pair(-8000L, 11.0)));
	EXPECT_TRUE(checkedInsert(testTree, std::make_pair(10L, 2.0)));

	SplayTree<long, double>::iterator foundIter = testTree.find(-8000L);

	ASSERT_NE(foundIter, testTree.end());
	EXPECT_EQ(foundIter->first, -8000L);

	// -4, the predecessor, should have been splayed to the root
	EXPECT_EQ(testTree.mRoot->getKey(), -8000L);
}

TEST(Find, SplayLastVisited)
{
	SplayTree<long, double> testTree;

	EXPECT_TRUE(checkedInsert(testTree, std::make_pair(1L, 2.0)));
	EXPECT_TRUE(checkedInsert(testTree, std::make_pair(-4L, 2.0)));
	EXPECT_TRUE(checkedInsert(testTree, std::make_pair(-8000L, 11.0)));
	EXPECT_TRUE(checkedInsert(testTree, std::make_pair(10L, 2.0)));

	SplayTree<long, double>::iterator foundIter = testTree.find(0L);

	EXPECT_EQ(foundIter, testTree.end());

	// the node does not exist but -4 should have been the last visited
	EXPECT_EQ(testTree.mRoot->getKey(), -4L);
}

TEST(Find, Random50x30_Exists)
{
	std::default_random_engine seedGenerator;
	seedGenerator.seed(987);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int counter = 0; counter < 50; ++counter)
	{

		int randomSeed1 = distributor(seedGenerator);
		int randomSeed2 = distributor(seedGenerator);

		// note: we do 30 random numbers because that creates an almost-full, but not overfull, graph on printBST
		std::set<int> randomData = makeRandomIntSet(30, randomSeed1);

		EXPECT_TRUE(fillSplayTreeRandomly(testTree, randomData, randomSeed2));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		// for each element in the tree, find it, and check that it was splayed
		for(std::set<int>::iterator dataIter = randomData.begin(); dataIter != randomData.end(); ++dataIter)
		{
			SplayTree<int, int>::iterator foundIter = testTree.find(*dataIter);

			// check that we even got the right element
			ASSERT_NE(foundIter, testTree.end());
			ASSERT_EQ(foundIter->first, *dataIter);

			// check that the element has been splayed to the root
			ASSERT_EQ(testTree.mRoot->getKey(), *dataIter);
		}

		testTree.clear();
	}


}

TEST(Find, Random50x30_Nonexistant)
{
	const int numElementsPerTree = 30;

	std::default_random_engine seedGenerator;
	seedGenerator.seed(987);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int testCounter = 0; testCounter < 50; ++testCounter)
	{

		int randomSeed1 = distributor(seedGenerator);
		int randomSeed2 = distributor(seedGenerator);
		int randomSeed3 = distributor(seedGenerator);

		// note: we do 30 random numbers because that creates an almost-full, but not overfull, graph on printBST
		std::set<int> randomData = makeRandomIntSet(numElementsPerTree, randomSeed1);

		EXPECT_TRUE(fillSplayTreeRandomly(testTree, randomData, randomSeed2));
		EXPECT_TRUE(verifyBST(testTree, randomData));

		// now try to find 30 things that don't exist, and check that their last-visited nodes were splayed

		std::default_random_engine randEngine;
		randEngine.seed(randomSeed3);
		// use same range as makeRandomIntSet()
		std::uniform_int_distribution<int> elementToFindDistributor(-1 * (numElementsPerTree), (numElementsPerTree) * 4);

		for(int counter = 0; counter < 50; ++counter)
		{
			int nonexistantKey;

			// make sure we get a key that isn't in the set
			do
			{
				nonexistantKey = elementToFindDistributor(randEngine);
			}
			while(randomData.find(nonexistantKey) != randomData.end());

			Node<int, int> * lastVisitedNode = getLastVisitedNode(testTree, nonexistantKey);

			SplayTree<int, int>::iterator elementIter = testTree.find(nonexistantKey);

			// check that we even got the right element
			ASSERT_EQ(elementIter, testTree.end());

			// check that the element has been splayed to the root
			ASSERT_EQ(testTree.mRoot->getKey(), lastVisitedNode->getKey());
		}

		testTree.clear();
	}


}
