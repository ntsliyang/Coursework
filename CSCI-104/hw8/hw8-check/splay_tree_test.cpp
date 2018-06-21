#include "../splayTree.h"
#include "gtest/gtest.h"
#include <random>
#include <algorithm>

template<typename Key, typename Value>
class InheritedBST : public SplayTree<Key, Value>
{
public:
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

class SplayTest : public testing::Test
{
protected:
	void stressTestInsert(size_t size, uint seed);
	void stressTestRemove(size_t size, uint seed);
};

void SplayTest::stressTestInsert(size_t size, uint seed)
{
	std::mt19937 g(seed);
	InheritedBST<int, int> bst;
	for (size_t i = 0; i < size; ++i)
	{
		bst.insert(std::make_pair(g(), 0));
	}
}

void SplayTest::stressTestRemove(size_t size, uint seed)
{
	std::mt19937 g(seed);
	std::vector<decltype(g)::result_type> v;
	InheritedBST<int, double> bst;
	for (size_t i = 0; i < size; ++i)
	{
		decltype(g)::result_type k = g();
		bst.insert(std::make_pair(k, 0));
		v.push_back(k);
	}

	std::shuffle(v.begin(), v.end(), g);
	for (size_t i = 0; i < v.size(); ++i)
	{
		bst.remove(v[i]);
	}
}

TEST_F(SplayTest, Test1_Construction)
{
	SplayTree<int, double> * spt = new SplayTree<int, double>();
	delete spt;
}

TEST_F(SplayTest, Test2_EmptyTree) 
{
	InheritedBST<int, double> bst;
	EXPECT_EQ(0, bst.height());
	EXPECT_EQ(true, bst.isBalanced());
}

TEST_F(SplayTest, Test3_SingleInsert) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	EXPECT_EQ(1, bst.height());
	EXPECT_EQ(true, bst.isBalanced());

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());
}

//[1, [2]] => [[1], 2]
TEST_F(SplayTest, Test4_TwoInsertSplay)
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(2, 2.0));
	// EXPECT_EQ(2, bst.height());
	// EXPECT_EQ(true, bst.isBalanced());

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());

	Node<int, double>* left = root->getLeft();

	ASSERT_NE(nullptr, left);
	EXPECT_EQ(1, left->getKey());
}

//[[[2], 1], 0] =>
//[0, [1, [2]]]
TEST_F(SplayTest, Test5_InsertZigZig)
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(2, 2.0));
	bst.insert(std::make_pair(0, 3.0));

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(0, root->getKey());

	Node<int, double>* right = root->getRight();
	ASSERT_NE(nullptr, right);
	EXPECT_EQ(1, right->getKey());

	Node<int, double>* rightRight = right->getRight();
	ASSERT_NE(nullptr, rightRight);
	EXPECT_EQ(2, rightRight->getKey());
}

//[1, [[2], 3]] =>
//[[1], 2, [3]]
TEST_F(SplayTest, Test6_InsertZigZag)
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(1, 2.0));
	bst.insert(std::make_pair(2, 3.0));

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());

	Node<int, double>* right = root->getRight();
	ASSERT_NE(nullptr, right);
	EXPECT_EQ(3, right->getKey());

	Node<int, double>* left = root->getLeft();
	ASSERT_NE(nullptr, left);
	EXPECT_EQ(1, left->getKey());
}


TEST_F(SplayTest, Test7_find)
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(2, 2.0));
	bst.insert(std::make_pair(0, 3.0));

	typename SplayTree<int, double>::iterator it;
	it = bst.find(2);
	ASSERT_NE(it, bst.end());
	EXPECT_EQ(it->second, 2.0);

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());
}

/* -----------------------------------
   For Students: Add more cases for find!

*/

TEST_F(SplayTest, Test8_findMin)
{
	InheritedBST<int, double> bst;

	//3 5 8 4 2 1 7 9 10 6
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(8, 1.0));
	bst.insert(std::make_pair(4, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(7, 1.0));
	bst.insert(std::make_pair(9, 1.0));
	bst.insert(std::make_pair(10, 1.0));
	bst.insert(std::make_pair(6, 1.0));

	typename SplayTree<int, double>::iterator it;
	it = bst.findMin();

	ASSERT_NE(it, bst.end());
	EXPECT_EQ(it->second, 1.0);

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());

	Node<int, double>* left = root->getLeft();
	ASSERT_EQ(nullptr, left);

	Node<int, double>* right = root->getRight();
	ASSERT_NE(nullptr, right);
	EXPECT_EQ(2, right->getKey());
}

TEST_F(SplayTest, Test9_findMax)
{
	InheritedBST<int, double> bst;

	//3 5 8 4 2 1 7 9 10 6
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(8, 1.0));
	bst.insert(std::make_pair(4, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(7, 1.0));
	bst.insert(std::make_pair(9, 1.0));
	bst.insert(std::make_pair(10, 1.0));
	bst.insert(std::make_pair(6, 1.0));

	typename SplayTree<int, double>::iterator it;
	it = bst.findMax();

	ASSERT_NE(it, bst.end());
	EXPECT_EQ(it->second, 1.0);

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(10, root->getKey());

	Node<int, double>* right = root->getRight();
	ASSERT_EQ(nullptr, right);

	Node<int, double>* left = root->getLeft();
	ASSERT_NE(nullptr, left);
	EXPECT_EQ(6, left->getKey());
}

TEST_F(SplayTest, Test10_remove)
{
	InheritedBST<int, double> bst;

	//3 5 8 4 2 1 7 9 10 6
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(8, 1.0));
	bst.insert(std::make_pair(4, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(7, 1.0));
	bst.insert(std::make_pair(9, 1.0));
	bst.insert(std::make_pair(10, 1.0));
	bst.insert(std::make_pair(6, 1.0));

	bst.remove(2);

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());

	Node<int, double>* right = root->getRight();
	ASSERT_NE(nullptr, right);
	EXPECT_EQ(6, right->getKey());

	Node<int, double>* left = root->getLeft();
	ASSERT_EQ(nullptr, left);
}

TEST_F(SplayTest, Stress1_Insert1000) 
{
	stressTestInsert(1000, 9527);
}

TEST_F(SplayTest, Stress2_Remove1000) 
{
	stressTestRemove(1000, 42);
}