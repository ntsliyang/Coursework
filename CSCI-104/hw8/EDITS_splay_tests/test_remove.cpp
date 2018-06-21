#include "splay_tests.h"

#include <gtest/gtest.h>

#include <initializer_list>
#include <utility>
#include <string>

// comment this if your one-child remove splays the predecessor
#define ONE_CHILD_REMOVE_SPLAYS_PARENT

/*
 * Test of remove functionality on the splay tree.
 */

TEST(Remove, EmptyTree)
{
	SplayTree<std::string, std::string> testTree;

	EXPECT_TRUE(checkedRemove(testTree, std::string("supercalifragilisticexpialodocious")));

	EXPECT_TRUE(verifyBST(testTree, {}));
}

TEST(Remove, NodeMismatch)
{
	SplayTree<std::string, std::string> testTree;

	ASSERT_TRUE(checkedInsert(testTree, std::make_pair<std::string, std::string>("blah", "blah")));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair<std::string, std::string>("bluh", "blug")));

	EXPECT_TRUE(checkedRemove(testTree, std::string("supercalifragilisticexpialodocious")));

	EXPECT_TRUE(verifyBST(testTree, {"blah", "bluh"}));
}

// uncomment for debug output
//#define DEBUG_REMOVE_BASIC

TEST(Remove, Basic)
{
	SplayTree<int, int> testTree;

	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(2, 8)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(1, -50)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(3, 0)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(10, 0)));
	ASSERT_TRUE(checkedInsert(testTree, std::make_pair(15, 0)));

#ifdef DEBUG_REMOVE_BASIC
	std::cout << "Before any removals, tree is: " << std::endl;
	prettyPrintBST(testTree);
#endif

	EXPECT_TRUE(checkedRemove(testTree, -1));
	EXPECT_TRUE(verifyBST(testTree, std::set<int>({2, 1, 3, 10, 15})));
	EXPECT_EQ(1, testTree.mRoot->getKey());

#ifdef DEBUG_REMOVE_BASIC
	std::cout << "After removing -1 (which doesn't exist), tree is: " << std::endl;
	prettyPrintBST(testTree);
#endif
	EXPECT_TRUE(checkedRemove(testTree, 2));
	EXPECT_TRUE(verifyBST(testTree, std::set<int>({1, 3, 10, 15})));

#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(10, testTree.mRoot->getKey());
#else
	ASSERT_EQ(3, testTree.mRoot->getKey());
#endif

#ifdef DEBUG_REMOVE_BASIC
	std::cout << "After removing 2, tree is: " << std::endl;
	prettyPrintBST(testTree);
#endif
	EXPECT_TRUE(checkedRemove(testTree, 10));
	EXPECT_TRUE(verifyBST(testTree, std::set<int>({1, 3, 15})));

#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(1, testTree.mRoot->getKey());
#else
	ASSERT_EQ(15, testTree.mRoot->getKey());
#endif

#ifdef DEBUG_REMOVE_BASIC
	std::cout << "After removing 10, tree is: " << std::endl;
	prettyPrintBST(testTree);
#endif

	EXPECT_TRUE(checkedRemove(testTree, 1));
	EXPECT_TRUE(verifyBST(testTree, std::set<int>({3, 15})));
	EXPECT_EQ(3, testTree.mRoot->getKey());

#ifdef DEBUG_REMOVE_BASIC
	std::cout << "After removing 1, tree is: " << std::endl;
	prettyPrintBST(testTree);
#endif

	EXPECT_TRUE(checkedRemove(testTree, 3));
	EXPECT_TRUE(verifyBST(testTree, std::set<int>({15})));
	EXPECT_EQ(15, testTree.mRoot->getKey());

#ifdef DEBUG_REMOVE_BASIC
	std::cout << "After removing 3, tree is: " << std::endl;
	prettyPrintBST(testTree);
#endif

	EXPECT_TRUE(checkedRemove(testTree, 15));
	EXPECT_TRUE(verifyBST(testTree, std::set<int>({})));

#ifdef DEBUG_REMOVE_BASIC
	std::cout << "After removing 15 (the last element), tree is: " << std::endl;
	prettyPrintBST(testTree);
#endif

	EXPECT_TRUE(checkedRemove(testTree, 15));
	EXPECT_TRUE(verifyBST(testTree, std::set<int>({})));

#ifdef DEBUG_REMOVE_BASIC
	std::cout << "After removing 15 (which doesn't exist), tree is: " << std::endl;
	prettyPrintBST(testTree);
#endif
}

// extensive combined insert-remove test
TEST(InsertRemove, Hard)
{
	SplayTree<int, string> b, c, d;
	pair<int, string> item5(5, "five");
	pair<int, string> item3(3, "three");
	pair<int, string> item7(7, "seven");
	pair<int, string> item4(4, "four");
	pair<int, string> item6(6, "six");
	pair<int, string> item9(9, "nine");
	pair<int, string> item10(10, "ten");
	pair<int, string> item2(2, "two");
	pair<int, string> item8(8, "eight");
	pair<int, string> item13(13, "thirteen");
	pair<int, string> item11(11, "eleven");
	pair<int, string> item12(12, "twelve");
	pair<int, string> item15(15, "fifteen");
	pair<int, string> item14(14, "fourteen");
	pair<int, string> item16(16, "sixteen");
	pair<int, string> item17(17, "seventeen");

	ASSERT_TRUE(checkedInsert(b, item5));
	ASSERT_TRUE(verifyBST(b, {item5.first}));

	ASSERT_TRUE(checkedRemove(b, 7));
	ASSERT_TRUE(verifyBST(b, {item5.first}));
	ASSERT_EQ(5, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 5));
	ASSERT_TRUE(verifyBST(b, {}));

	ASSERT_TRUE(checkedInsert(b, item5));
	ASSERT_TRUE(checkedInsert(b, item3));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first}));
	ASSERT_EQ(3, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 5));
	ASSERT_TRUE(verifyBST(b, {item3.first}));

	ASSERT_TRUE(checkedRemove(b, 3));
	ASSERT_TRUE(verifyBST(b, {}));

	ASSERT_TRUE(checkedInsert(b, item5));
	ASSERT_TRUE(checkedInsert(b, item3));
	ASSERT_TRUE(checkedInsert(b, item7));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first}));
	ASSERT_EQ(7, b.mRoot->getKey());
	ASSERT_TRUE(checkedRemove(b, 5));
	ASSERT_TRUE(verifyBST(b, {item3.first, item7.first}));
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(7, b.mRoot->getKey());
#else
	ASSERT_EQ(3, b.mRoot->getKey());
#endif
	ASSERT_TRUE(checkedRemove(b, 7));
	ASSERT_TRUE(verifyBST(b, {item3.first}));
	ASSERT_EQ(3, b.mRoot->getKey());
	ASSERT_TRUE(checkedRemove(b, 3));
	ASSERT_TRUE(verifyBST(b, {}));
	ASSERT_TRUE(checkedInsert(b, item5));
	ASSERT_TRUE(checkedInsert(b, item3));
	ASSERT_TRUE(checkedInsert(b, item7));
	ASSERT_TRUE(checkedInsert(b, item4));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first}));
	ASSERT_EQ(4, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 5));
	ASSERT_TRUE(verifyBST(b, {item3.first, item7.first, item4.first}));
	ASSERT_EQ(7, b.mRoot->getKey());
	b.clear();
	ASSERT_TRUE(verifyBST(b, {}));

	ASSERT_TRUE(checkedInsert(b, item5));
	ASSERT_TRUE(checkedInsert(b, item3));
	ASSERT_TRUE(checkedInsert(b, item7));
	ASSERT_TRUE(checkedInsert(b, item4));
	ASSERT_TRUE(checkedInsert(b, item6));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first}));
	ASSERT_EQ(6, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 6));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first}));
	ASSERT_EQ(4, b.mRoot->getKey());
	ASSERT_TRUE(checkedRemove(b, 4));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first}));
	ASSERT_EQ(3, b.mRoot->getKey());

	b.clear();
	ASSERT_TRUE(verifyBST(b, {}));

	ASSERT_TRUE(checkedInsert(b, item5));
	ASSERT_TRUE(checkedInsert(b, item3));
	ASSERT_TRUE(checkedInsert(b, item7));
	ASSERT_TRUE(checkedInsert(b, item4));
	ASSERT_TRUE(checkedInsert(b, item6));
	ASSERT_TRUE(checkedInsert(b, item9));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first}));
	ASSERT_TRUE(checkedRemove(b, 5));
	ASSERT_TRUE(verifyBST(b, {item3.first, item7.first, item4.first, item6.first, item9.first}));
	ASSERT_EQ(4, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 7));
	ASSERT_TRUE(verifyBST(b, {item3.first, item4.first, item6.first, item9.first}));
	ASSERT_EQ(6, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 6));
	ASSERT_TRUE(verifyBST(b, {item3.first, item4.first, item9.first}));
	ASSERT_EQ(4, b.mRoot->getKey());
	b.clear();
	ASSERT_TRUE(verifyBST(b, {}));

	ASSERT_TRUE(checkedInsert(b, item5));
	ASSERT_TRUE(checkedInsert(b, item3));
	ASSERT_TRUE(checkedInsert(b, item7));
	ASSERT_TRUE(checkedInsert(b, item4));
	ASSERT_TRUE(checkedInsert(b, item6));
	ASSERT_TRUE(checkedInsert(b, item9));
	ASSERT_TRUE(checkedInsert(b, item10));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
			item9.first, item10.first}));
	ASSERT_EQ(10, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 5));
	ASSERT_TRUE(verifyBST(b, {item3.first, item7.first, item4.first, item6.first,
				item9.first, item10.first}));
	ASSERT_EQ(4, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 9));
	ASSERT_TRUE(verifyBST(b, {item3.first, item7.first, item4.first, item6.first, item10.first}));
	ASSERT_EQ(6, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 3));
	ASSERT_TRUE(verifyBST(b, {item7.first, item4.first, item6.first, item10.first}));
	ASSERT_EQ(4, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 7));
	ASSERT_TRUE(verifyBST(b, {item4.first, item6.first, item10.first}));
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(6, b.mRoot->getKey());
#else
	ASSERT_EQ(10, b.mRoot->getKey());
#endif

	ASSERT_TRUE(checkedRemove(b, 4));
	ASSERT_TRUE(verifyBST(b, {item6.first, item10.first}));
	ASSERT_EQ(6, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 10));
	ASSERT_TRUE(verifyBST(b, {item6.first}));
	ASSERT_EQ(6, b.mRoot->getKey());
	ASSERT_TRUE(checkedRemove(b, 10));
	ASSERT_TRUE(verifyBST(b, {item6.first}));
	ASSERT_EQ(6, b.mRoot->getKey());
	ASSERT_TRUE(checkedRemove(b, 6));
	ASSERT_TRUE(verifyBST(b, {}));
	
	ASSERT_TRUE(checkedInsert(b, item5));
	ASSERT_TRUE(checkedInsert(b, item3));
	ASSERT_TRUE(checkedInsert(b, item7));
	ASSERT_TRUE(checkedInsert(b, item4));
	ASSERT_TRUE(checkedInsert(b, item6));
	ASSERT_TRUE(checkedInsert(b, item9));
	ASSERT_TRUE(checkedInsert(b, item10));
	ASSERT_TRUE(checkedInsert(b, item2));
	ASSERT_TRUE(checkedInsert(b, item8));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
					item9.first, item10.first, item2.first, item8.first}));

	ASSERT_TRUE(checkedInsert(b, item13));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
					item9.first, item10.first, item2.first, item8.first, item13.first}));

	ASSERT_TRUE(checkedInsert(b, item12));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
					item9.first, item10.first, item2.first, item8.first, item13.first, item12.first}));

	ASSERT_TRUE(checkedInsert(b, item11));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
					item9.first, item10.first, item2.first, item8.first, item13.first,
					item12.first, item11.first}));

	ASSERT_TRUE(checkedRemove(b, 13));
	
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
					item9.first, item10.first, item2.first, item8.first,
					item12.first, item11.first}));
	ASSERT_EQ(12, b.mRoot->getKey());
	ASSERT_TRUE(checkedRemove(b, 12));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first,
					item9.first, item10.first, item2.first, item8.first, item11.first}));
	ASSERT_EQ(11, b.mRoot->getKey());
	ASSERT_TRUE(checkedRemove(b, 10));
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(11, b.mRoot->getKey());
#else
	ASSERT_EQ(8, b.mRoot->getKey());
#endif
	ASSERT_TRUE(checkedRemove(b, 13));
	ASSERT_EQ(11, b.mRoot->getKey());

	ASSERT_TRUE(checkedRemove(b, 7));
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(2, b.mRoot->getKey());
#else
	ASSERT_EQ(6, b.mRoot->getKey());
#endif
	ASSERT_TRUE(checkedRemove(b, 8));
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(6, b.mRoot->getKey());
#else
	ASSERT_EQ(9, b.mRoot->getKey());
#endif
	ASSERT_TRUE(checkedRemove(b, 7));
	ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item4.first, item6.first,
					item9.first, item2.first, item11.first}));
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(9, b.mRoot->getKey());
#else
	ASSERT_EQ(6, b.mRoot->getKey());
#endif

	ASSERT_TRUE(checkedInsert(d, item10));
	ASSERT_TRUE(checkedInsert(d, item3));
	ASSERT_TRUE(checkedInsert(d, item2));
	ASSERT_TRUE(checkedInsert(d, item15));
	ASSERT_TRUE(checkedInsert(d, item12));
	ASSERT_TRUE(checkedInsert(d, item11));
	ASSERT_TRUE(checkedInsert(d, item14));
	ASSERT_TRUE(checkedInsert(d, item13));
	ASSERT_TRUE(checkedInsert(d, item16));
	ASSERT_TRUE(checkedInsert(d, item17));

	ASSERT_TRUE(verifyBST(d, {item10.first, item3.first, item2.first, item15.first, item12.first,
					item11.first, item14.first, item13.first, item16.first,
					item17.first}));

	ASSERT_TRUE(checkedRemove(d, 15));

	ASSERT_TRUE(verifyBST(d, {item10.first, item3.first, item2.first, item12.first,
					item11.first, item14.first, item13.first, item16.first,
					item17.first}));
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(13, d.mRoot->getKey());
#else
	ASSERT_EQ(14, d.mRoot->getKey());
#endif
	ASSERT_TRUE(checkedRemove(d, 10));
	ASSERT_TRUE(verifyBST(d, {item3.first, item2.first, item12.first,
					item11.first, item14.first, item13.first, item16.first,
					item17.first}));
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
	ASSERT_EQ(11, d.mRoot->getKey());
#else
	ASSERT_EQ(2, d.mRoot->getKey());
#endif
	ASSERT_TRUE(checkedInsert(c, item5));
	ASSERT_TRUE(checkedInsert(c, item3));
	ASSERT_TRUE(checkedInsert(c, item7));
	ASSERT_TRUE(checkedInsert(c, item4));
	ASSERT_TRUE(checkedInsert(c, item6));
	ASSERT_TRUE(checkedInsert(c, item9));
	ASSERT_TRUE(checkedInsert(c, item10));
	ASSERT_TRUE(checkedInsert(c, item2));
	ASSERT_TRUE(checkedInsert(c, item8));
	ASSERT_TRUE(checkedInsert(c, item15));
	ASSERT_TRUE(checkedInsert(c, item11));
	ASSERT_TRUE(checkedInsert(c, item14));
	ASSERT_TRUE(checkedInsert(c, item13));
	ASSERT_TRUE(checkedInsert(c, item12));

	ASSERT_TRUE(verifyBST(c, {item5.first, item3.first, item7.first, item4.first, item6.first,
					item9.first, item10.first, item2.first, item8.first, item15.first,
					item11.first, item14.first, item13.first, item12.first}));
	ASSERT_TRUE(checkedRemove(c, 15));
	ASSERT_EQ(14, c.mRoot->getKey());
	ASSERT_TRUE(checkedRemove(c, 14));
	ASSERT_TRUE(verifyBST(c, {item5.first, item3.first, item7.first, item4.first, item6.first,
					item9.first, item10.first, item2.first, item8.first,
					item11.first, item13.first, item12.first}));
	ASSERT_EQ(13, c.mRoot->getKey());
}
TEST(Remove, Random50x30ele)
{
	std::default_random_engine seedGenerator;
	seedGenerator.seed(2002);
	std::uniform_int_distribution<int> distributor(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	SplayTree<int, int> testTree;

	for(int counter = 0; counter < 50; ++counter)
	{

		int randomSeed1 = distributor(seedGenerator);
		int randomSeed2 = distributor(seedGenerator);
		int randomSeed3 = distributor(seedGenerator);

		// create tree of random data
		std::set<int> randomData = makeRandomIntSet(30, randomSeed1);
		fillSplayTreeRandomly(testTree, randomData, randomSeed2);

		ASSERT_TRUE(verifyBST(testTree, randomData));

		// now remove elements at random
		std::vector<int> randomDataVector(randomData.begin(), randomData.end());
		std::default_random_engine shuffleRandEngine;
		shuffleRandEngine.seed(randomSeed3);
		std::shuffle(randomDataVector.begin(), randomDataVector.end(), shuffleRandEngine);

		for(size_t elementIndex = 0; elementIndex < randomDataVector.size(); ++elementIndex)
		{
			//EXPECT_TRUE(checkedRemove(testTree, randomDataVector[elementIndex]));
			testTree.remove(randomDataVector[elementIndex]);
			randomData.erase(randomData.find(randomDataVector[elementIndex]));

			ASSERT_TRUE(verifyBST(testTree, randomData));

		}
	}


}

// The following are the official hw7-check remove tests (which are very well thought-out)
// but augmented with the EDITS verification functions

TEST(InstructorRemoveTest, SingleRemove)
{
	SplayTree<int, double> bst;
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(1, 1.0)));
	EXPECT_TRUE(checkedRemove(bst, 1));

	EXPECT_TRUE(verifyBST(bst, {}));
}

TEST(InstructorRemoveTest, RightChildRemove)
{
	SplayTree<int, double> bst;
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(1, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(2, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(3, 1.0)));
	EXPECT_TRUE(checkedRemove(bst, 1));

	EXPECT_TRUE(verifyBST(bst, {2, 3}));
}

TEST(InstructorRemoveTest, LeftChildRemove)
{
	SplayTree<int, double> bst;
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(3, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(2, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(1, 1.0)));
	EXPECT_TRUE(checkedRemove(bst, 3));

	EXPECT_TRUE(verifyBST(bst, {1, 2}));
}


// uncomment to print trees for all instructor tests.
//#define DEBUG_INSTRUCTOR_REMOVE

TEST(InstructorRemoveTest, OneChildRemove)
{
	SplayTree<int, double> bst;
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(2, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(1, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(3, 1.0)));

#ifdef DEBUG_INSTRUCTOR_REMOVE
	prettyPrintBST(bst);
	std::cout << "Removing key 2" << std::endl;
#endif

	EXPECT_TRUE(checkedRemove(bst, 2));

#ifdef DEBUG_INSTRUCTOR_REMOVE
	prettyPrintBST(bst);
#endif

	EXPECT_TRUE(verifyBST(bst, {1, 3}));

	ASSERT_NE(nullptr, bst.mRoot);

	if(bst.mRoot->getKey() == 3)
	{
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
		std::cout << ">> INFO: you have implemented one-child remove by splaying the parent" << std::endl;
#else
		std::cout << ">> ERROR: you have implemented one-child remove by splaying the parent" << std::endl;
		std::cout << ">> Please uncomment line 10 of test_remove.cpp!" << std::endl;
		FAIL();
#endif

		EXPECT_EQ(3, bst.mRoot->getKey());

		ASSERT_NE(nullptr, bst.mRoot->getLeft());
		EXPECT_EQ(1, bst.mRoot->getLeft()->getKey());

		ASSERT_EQ(nullptr, bst.mRoot->getRight());
	}
	else
	{
#ifdef ONE_CHILD_REMOVE_SPLAYS_PARENT
		std::cout << ">> ERROR: you have implemented one-child remove by splaying the predecessor" << std::endl;
		std::cout << ">> Please comment line 10 of test_remove.cpp!" << std::endl;
		FAIL();
#else
		std::cout << ">> INFO: you have implemented one-child remove by splaying the predecessor" << std::endl;
#endif

		EXPECT_EQ(1, bst.mRoot->getKey());

		ASSERT_NE(nullptr, bst.mRoot->getRight());
		EXPECT_EQ(3, bst.mRoot->getRight()->getKey());

		ASSERT_EQ(nullptr, bst.mRoot->getLeft());
	}

}


TEST(InstructorRemoveTest, RemoveChild)
{
	SplayTree<int, double> bst;
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(5, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(2, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(6, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(4, 1.0)));

#ifdef DEBUG_INSTRUCTOR_REMOVE
	prettyPrintBST(bst);
	std::cout << "Removing key 5" << std::endl;
#endif

	EXPECT_TRUE(checkedRemove(bst, 5));

#ifdef DEBUG_INSTRUCTOR_REMOVE
	prettyPrintBST(bst);
#endif

	EXPECT_TRUE(verifyBST(bst, {2, 6, 4}));

	ASSERT_NE(nullptr, bst.mRoot);
	EXPECT_EQ(6, bst.mRoot->getKey());

	ASSERT_NE(nullptr, bst.mRoot->getLeft());
	EXPECT_EQ(4, bst.mRoot->getLeft()->getKey());

	ASSERT_NE(nullptr, bst.mRoot->getLeft()->getLeft());
	EXPECT_EQ(2, bst.mRoot->getLeft()->getLeft()->getKey());
}

TEST(InstructorRemoveTest, TwoChildrenRemove_SwapChild)
{
	SplayTree<int, double> bst;
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(3, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(1, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(2, 1.0)));

#ifdef DEBUG_INSTRUCTOR_REMOVE
	prettyPrintBST(bst);
	std::cout << "Removing key 2" << std::endl;
#endif

	EXPECT_TRUE(checkedRemove(bst, 2));

#ifdef DEBUG_INSTRUCTOR_REMOVE
	prettyPrintBST(bst);
#endif

	EXPECT_TRUE(verifyBST(bst, {1, 3}));

	ASSERT_NE(nullptr, bst.mRoot);
	EXPECT_EQ(1, bst.mRoot->getKey());

	ASSERT_NE(nullptr, bst.mRoot->getRight());
	EXPECT_EQ(3, bst.mRoot->getRight()->getKey());

	ASSERT_EQ(nullptr, bst.mRoot->getLeft());
}


TEST(InstructorRemoveTest, TwoChildrenRemove_SwapPred)
{
	SplayTree<int, double> bst;
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(4, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(2, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(6, 1.0)));
	ASSERT_TRUE(checkedInsert(bst, std::make_pair(5, 1.0)));

#ifdef DEBUG_INSTRUCTOR_REMOVE
	prettyPrintBST(bst);
	std::cout << "Removing key 5" << std::endl;
#endif

	EXPECT_TRUE(checkedRemove(bst, 5));

#ifdef DEBUG_INSTRUCTOR_REMOVE
	prettyPrintBST(bst);
#endif

	EXPECT_TRUE(verifyBST(bst, {2, 6, 4}));

	ASSERT_NE(nullptr, bst.mRoot);
	EXPECT_EQ(4, bst.mRoot->getKey());

	ASSERT_NE(nullptr, bst.mRoot->getLeft());
	EXPECT_EQ(2, bst.mRoot->getLeft()->getKey());

	ASSERT_NE(nullptr, bst.mRoot->getRight());
	EXPECT_EQ(6, bst.mRoot->getRight()->getKey());
}


