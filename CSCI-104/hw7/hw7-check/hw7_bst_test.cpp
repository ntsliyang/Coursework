#include "../bst.h"
#include "gtest/gtest.h"
#include <random>
#include <algorithm>

template<typename Key, typename Value>
class InheritedBST : public BinarySearchTree<Key, Value>
{
public:
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

class BSTTest : public testing::Test 
{
protected:
	void stressTestInsert(size_t size, uint seed);
	void stressTestRemove(size_t size, uint seed);
};

void BSTTest::stressTestInsert(size_t size, uint seed)
{
	std::mt19937 g(seed);
	InheritedBST<int, int> bst;
	for (size_t i = 0; i < size; ++i)
	{
		bst.insert(std::make_pair(g(), 0));
	}
}

void BSTTest::stressTestRemove(size_t size, uint seed)
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

TEST_F(BSTTest, Test1_Construction) 
{
	BinarySearchTree<int, double>* bst = new BinarySearchTree<int, double>();
	delete bst;
}

TEST_F(BSTTest, Test2_EmptyTree) 
{
	InheritedBST<int, double> bst;
	EXPECT_EQ(0, bst.height());
	EXPECT_EQ(true, bst.isBalanced());
}

TEST_F(BSTTest, Test3_SingleInsert) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	EXPECT_EQ(1, bst.height());
	EXPECT_EQ(true, bst.isBalanced());

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());
}

TEST_F(BSTTest, Test4_BalancedInsert) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	EXPECT_EQ(2, bst.height());
	EXPECT_EQ(true, bst.isBalanced());

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(3, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(1, root->getLeft()->getKey());
}

TEST_F(BSTTest, Test5_UnbalancedInsert) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	EXPECT_EQ(3, bst.height());
	EXPECT_EQ(false, bst.isBalanced());

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(2, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getRight());
	EXPECT_EQ(3, root->getRight()->getRight()->getKey());
}

TEST_F(BSTTest, Test6_SingleRemove) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.remove(1);
	EXPECT_EQ(0, bst.height());
	EXPECT_EQ(true, bst.isBalanced());
}

TEST_F(BSTTest, Test7_RightChildRemove) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	bst.remove(1);
	EXPECT_EQ(2, bst.height());
	EXPECT_EQ(true, bst.isBalanced());
}

TEST_F(BSTTest, Test8_LeftChildRemove) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.remove(3);
	EXPECT_EQ(2, bst.height());
	EXPECT_EQ(true, bst.isBalanced());
}

TEST_F(BSTTest, Test9_TwoChildrenRemove) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	bst.remove(2);
	EXPECT_EQ(2, bst.height());
	EXPECT_EQ(true, bst.isBalanced());

	// predecessor, 1, should be promoted
	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(3, root->getRight()->getKey());

	ASSERT_EQ(nullptr, root->getLeft());
}

TEST_F(BSTTest, Test10_TwoChildrenRemove) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(6, 1.0));
	bst.insert(std::make_pair(4, 1.0));
	bst.remove(5);
	EXPECT_EQ(2, bst.height());
	EXPECT_EQ(true, bst.isBalanced());

	// predecessor, 4, should be promoted
	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(4, root->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(6, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(2, root->getLeft()->getKey());
}

TEST_F(BSTTest, Test11_InsertAfterClear) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(7, 1.0));
	bst.insert(std::make_pair(9, 1.0));
	bst.clear();
	bst.insert(std::make_pair(1, 1.0));
	EXPECT_EQ(1, bst.height());
	EXPECT_EQ(true, bst.isBalanced());

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());
}

TEST_F(BSTTest, Test11_InsertAfterRemoveRoot) 
{
	InheritedBST<int, double> bst;
	bst.insert(std::make_pair(5, 1.0));
	bst.remove(5);
	bst.insert(std::make_pair(1, 1.0));
	EXPECT_EQ(1, bst.height());
	EXPECT_EQ(true, bst.isBalanced());

	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());
}

TEST_F(BSTTest, Stress1_Insert1000) 
{
	stressTestInsert(1000, 17);
}

TEST_F(BSTTest, Stress2_Remove1000) 
{
	stressTestRemove(1000, 37);
}