#include "splayTree.h"
#include "gtest/gtest.h"

template<typename Key, typename Value>
class InheritedBST : public SplayTree<Key, Value>
{
public:
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

class SplayTest : public testing::Test
{};

TEST_F(SplayTest, Test1_RemoveEmpty)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	Node<int, double>* root = spt->getRoot();
	spt->remove(5);
	
	// ASSERT_EQ(nullptr, root);
	EXPECT_EQ(NULL, root);

	spt->deleteMinLeaf();
	EXPECT_EQ(NULL, root);
	spt->deleteMaxLeaf();
	EXPECT_EQ(NULL, root);
	auto i = spt->findMax();
	EXPECT_EQ(spt->end(), i);
	auto j = spt->findMin();
	EXPECT_EQ(spt->end(), j);
	auto k = spt->find(5);
	EXPECT_EQ(spt->end(), k);
	delete spt;
}

TEST_F(SplayTest, Test2_RemoveUnfound)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	Node<int, double>* root = spt->getRoot();
	spt->remove(5);
	
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getLeft());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getRight());

	spt->deleteMinLeaf();
	EXPECT_EQ(nullptr, spt->getRoot());

	spt->insert(std::make_pair(1, 1.0));;
	spt->deleteMaxLeaf();
	EXPECT_EQ(nullptr, spt->getRoot());

	spt->insert(std::make_pair(1, 1.0));
	auto i = spt->findMax();
	ASSERT_NE(0, (*i).first);
	EXPECT_EQ(1, (*i).first);
	
	auto j = spt->findMin();
	ASSERT_NE(0, (*j).first);
	EXPECT_EQ(1, (*j).first);

	auto k = spt->find(123);
	// ASSERT_NE(this->end(), k);
	EXPECT_EQ(spt->end(), k);

	auto g = spt->find(1);
	// ASSERT_NE(0, (*j).first);
	EXPECT_EQ(1, (*g).first);
	delete spt;
}

TEST_F(SplayTest, Test3_InsertRepetition)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(2, 1.0));
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(1, 1.0));
	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(2, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getRight());
	EXPECT_EQ(9, root->getRight()->getRight()->getKey());

	spt->insert(std::make_pair(2, 1.0));
	root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(1, root->getLeft()->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(9, root->getRight()->getKey());

	spt->insert(std::make_pair(3, 1.0));
	spt->remove(3);
	root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(1, root->getLeft()->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(9, root->getRight()->getKey());

	delete spt;
}

TEST_F(SplayTest, Test4_FindRepetition)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(2, 1.0));
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(1, 1.0));
	spt->find(2);
	spt->find(1);
	spt->find(1);
	spt->find(9);
	Node<int, double>* root = spt->getRoot();
	
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(9, root->getKey());

	ASSERT_NE(nullptr, root->getLeft()->getLeft());
	EXPECT_EQ(1, root->getLeft()->getLeft()->getKey());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getRight());
	delete spt;
}

TEST_F(SplayTest, Test5_RemoveLeaf) 
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(4, 1.0));
	spt->insert(std::make_pair(3, 1.0));
	spt->insert(std::make_pair(2, 1.0));
	spt->remove(1);
	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(3, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getRight());
	EXPECT_EQ(4, root->getRight()->getRight()->getKey());

	spt->remove(2);
	root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(3, root->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(4, root->getRight()->getKey());

	delete spt;
}

TEST_F(SplayTest, Test6_RemoveRightParent) 
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(12, 1.0));
	spt->insert(std::make_pair(14, 1.0));
	spt->insert(std::make_pair(13, 1.0));
	spt->insert(std::make_pair(15, 1.0));
	spt->insert(std::make_pair(10, 1.0));
	spt->insert(std::make_pair(11, 1.0));

	spt->remove(14);
	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(13, root->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(12, root->getLeft()->getKey());

	ASSERT_NE(nullptr, root->getLeft()->getLeft());
	EXPECT_EQ(11, root->getLeft()->getLeft()->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(15, root->getRight()->getKey());
	delete spt;
}


TEST_F(SplayTest, Test7_RemoveRightChild) 
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(5, 1.0));
	spt->insert(std::make_pair(3, 1.0));
	spt->insert(std::make_pair(8, 1.0));
	spt->insert(std::make_pair(12, 1.0));
	spt->insert(std::make_pair(6, 1.0));
	spt->remove(12);
	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(6, root->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(5, root->getLeft()->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(8, root->getRight()->getKey());

	delete spt;
}

TEST_F(SplayTest, Test8_RemoveLeftParent) 
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(12, 1.0));
	spt->insert(std::make_pair(14, 1.0));
	spt->insert(std::make_pair(13, 1.0));
	spt->insert(std::make_pair(15, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(10, 1.0));
	spt->insert(std::make_pair(11, 1.0));
	spt->insert(std::make_pair(8, 1.0));
	spt->insert(std::make_pair(78, 1.0));
	spt->insert(std::make_pair(56, 1.0));

	spt->remove(12);
	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(8, root->getLeft()->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(56, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getRight());
	EXPECT_EQ(78, root->getRight()->getRight()->getKey());
	delete spt;
}

TEST_F(SplayTest, Test9_RemoveLeftChild) 
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(12, 1.0));
	spt->insert(std::make_pair(14, 1.0));
	spt->insert(std::make_pair(13, 1.0));
	spt->insert(std::make_pair(15, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(10, 1.0));
	spt->insert(std::make_pair(11, 1.0));

	spt->remove(9);
	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getLeft());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(11, root->getRight()->getKey());

	delete spt;
}

TEST_F(SplayTest, Test10_RemoveRoot) 
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(12, 1.0));
	spt->insert(std::make_pair(14, 1.0));
	spt->insert(std::make_pair(13, 1.0));
	spt->insert(std::make_pair(15, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(10, 1.0));
	spt->insert(std::make_pair(11, 1.0));

	spt->remove(11);
	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(nullptr, root->getParent());

	ASSERT_NE(nullptr, root);
	EXPECT_EQ(10, root->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(12, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(9, root->getLeft()->getKey());
	delete spt;
}

