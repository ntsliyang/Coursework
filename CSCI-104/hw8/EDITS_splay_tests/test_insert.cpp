#include "splay_tests.h"

#include <gtest/gtest.h>

#include <initializer_list>
#include <set>
#include <utility>

/*
 * Test file for splay tree insert.
 * Tests a few basic
 */

TEST(Insert, JustRoot)
{
	SplayTree<std::string, std::string> testTree;

	ASSERT_TRUE(checkedInsert(testTree, std::make_pair<std::string, std::string>("Hello World", "!!!")));

	EXPECT_TRUE(verifyBST(testTree, std::set<std::string>({"Hello World"})));
}

TEST(Insert, Basic)
{
	SplayTree<int, int> testTree;

	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(5, 8)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(3, 159)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(1, 9)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(10, 0x5a)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(15, 0xb)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(2, 4)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(4, 159)));

	EXPECT_TRUE(verifyBST(testTree, std::set<int>({5, 3, 1, 10, 15, 2, 4})));

	//EXPECT_TRUE(verifyBST(testTree, {1, 2, 3}));
}

TEST(Insert, Duplicates)
{
	SplayTree<int, int> testTree;

	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(5, 8)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(3, 159)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(1, 9)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(3, 0x5a)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(15, 0xb)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(1, 4)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(3, 159)));

	EXPECT_TRUE(verifyBST(testTree, std::set<int>({5, 3, 1, 15})));

	//EXPECT_TRUE(verifyBST(testTree, {1, 2, 3}));
}


TEST(Insert, Random50x30_RandomOrder)
{

	// hey, I heard you liked random numbers
	// so, I put some random numbers in your random numbers
	std::default_random_engine seedGenerator;
	seedGenerator.seed(7777);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int counter = 0; counter < 50; ++counter)
	{

		int randomSeed1 = distributor(seedGenerator);
		int randomSeed2 = distributor(seedGenerator);

		// note: we do 30 random numbers because that creates an almost-full, but not overfull, graph on printBST
		std::set<int> randomData = makeRandomIntSet(30, randomSeed1);

		EXPECT_TRUE(fillSplayTreeRandomly(testTree, randomData, randomSeed2));
		//prettyPrintBST(testTree);
		EXPECT_TRUE(verifyBST(testTree, randomData));

		testTree.clear();
	}


}

TEST(Insert, Random50x30_SortedOrder)
{

	std::default_random_engine seedGenerator;
	seedGenerator.seed(0);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int counter = 0; counter < 50; ++counter)
	{

		int randomSeed1 = distributor(seedGenerator);

		std::set<int> randomData = makeRandomIntSet(30, randomSeed1);
		EXPECT_TRUE(fillSplayTreeInOrder(testTree, randomData));
		//prettyPrintBST(testTree);
		EXPECT_TRUE(verifyBST(testTree, randomData));

		testTree.clear();
	}


}

TEST(Insert, Random50x30_AlternatingOrder)
{

	std::default_random_engine seedGenerator;
	seedGenerator.seed(1962);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int counter = 0; counter < 50; ++counter)
	{

		int randomSeed1 = distributor(seedGenerator);

		std::set<int> randomData = makeRandomIntSet(30, randomSeed1);
		EXPECT_TRUE(fillSplayTreeAlternating(testTree, randomData));
		//prettyPrintBST(testTree);
		EXPECT_TRUE(verifyBST(testTree, randomData));

		testTree.clear();
	}


}

TEST(Insert, Random1000ele_RandomOrder)
{

	std::default_random_engine seedGenerator;
	seedGenerator.seed(1860);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;
	int randomSeed1 = distributor(seedGenerator);
	int randomSeed2 = distributor(seedGenerator);

	std::set<int> randomData = makeRandomIntSet(1000, randomSeed1);
	EXPECT_TRUE(fillSplayTreeRandomly(testTree, randomData, randomSeed2));
	EXPECT_TRUE(verifyBST(testTree, randomData));

	testTree.clear();

}

TEST(Insert, Random1000ele_SequentialOrder)
{

	std::default_random_engine seedGenerator;
	seedGenerator.seed(-7000);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;
	int randomSeed1 = distributor(seedGenerator);

	std::set<int> randomData = makeRandomIntSet(1000, randomSeed1);
	EXPECT_TRUE(fillSplayTreeInOrder(testTree, randomData));
	EXPECT_TRUE(verifyBST(testTree, randomData));

	testTree.clear();

}

// inserts elements in the worst possible runtime order
TEST(Insert, Random1000ele_WorstCaseOrder)
{

	std::default_random_engine seedGenerator;
	seedGenerator.seed(19);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;
	int randomSeed1 = distributor(seedGenerator);

	std::set<int> randomData = makeRandomIntSet(1000, randomSeed1);
	EXPECT_TRUE(fillSplayTreeAlternating(testTree, randomData));
	EXPECT_TRUE(verifyBST(testTree, randomData));

	testTree.clear();
}

/* Commented because it takes a bit too long to run,
 * but uncomment for a REALLY stressful stress test!

TEST(Insert, Random100000ele)
{

	BinarySearchTree<int, int> testTree;

	int randomSeed1 = 1668, randomSeed2 = -5000;

	std::set<int> randomData = makeRandomIntSet(100000, randomSeed1);
	fillTree(testTree, randomData, randomSeed2);
	EXPECT_TRUE(verifyBST(testTree, randomData));

}

*/
