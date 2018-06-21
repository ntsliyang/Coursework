#include "../splayTree.h"
#include "../cacheLRU.h"
#include "gtest/gtest.h"
#include <random>
#include <algorithm>

template<typename Key, typename Value>
class InheritedBST : public SplayTree<Key, Value>
{
public:
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

template<typename Key, typename Value>
class InheritedLRU : public cacheLRU<Key, Value>
{
public:
	InheritedLRU(int i );
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

template<typename Key, typename Value>
InheritedLRU<Key, Value>::InheritedLRU(int i)
: cacheLRU<Key, Value>(i){}

class SplayTest : public testing::Test
{};

TEST_F(SplayTest, Test1_PiazzaFAQ)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(4, 1.0));
	spt->insert(std::make_pair(5, 1.0));

	spt->insert(std::make_pair(8, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(3, 1.0));
	spt->insert(std::make_pair(7, 1.0));

	spt->remove(3);

	Node<int, double>* root = spt->getRoot();


	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());

	EXPECT_EQ(nullptr, root->getLeft());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(7, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getRight());
	EXPECT_EQ(9, root->getRight()->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getLeft());
	EXPECT_EQ(5, root->getRight()->getLeft()->getKey());


	delete spt;
}

TEST_F(SplayTest, Test2_PiazzaFAQ)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(4, 1.0));
	spt->insert(std::make_pair(5, 1.0));

	spt->insert(std::make_pair(8, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(3, 1.0));
	spt->insert(std::make_pair(7, 1.0));

	spt->remove(7);

	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(3, root->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(1, root->getLeft()->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(5, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getRight());
	EXPECT_EQ(9, root->getRight()->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getLeft());
	EXPECT_EQ(4, root->getRight()->getLeft()->getKey());

	delete spt;
}

TEST_F(SplayTest, Test_PiazzaFindMin)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	SplayTree<int, double>::iterator it = spt->findMin();
	ASSERT_EQ(it, spt->end());
	delete spt;
}

/*
Checks find max returns empty if element not found
*/
TEST_F(SplayTest, Test_PiazzaFindMax)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	SplayTree<int, double>::iterator it = spt->findMax();
	ASSERT_EQ(it, spt->end());
	delete spt;
}


/**
checks that you do not use findMin in delete (4 should be removed, not 3)
*/
TEST_F(SplayTest, Test_PiazzaDeleteNoFindMin)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(4, 1.0));
	spt->insert(std::make_pair(5, 1.0));

	spt->insert(std::make_pair(8, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(3, 1.0));
	spt->insert(std::make_pair(7, 1.0));

	spt->deleteMinLeaf();

	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(5, root->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(3, root->getLeft()->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(7, root->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getRight());
	EXPECT_EQ(8, root->getRight()->getRight()->getKey());

	ASSERT_NE(nullptr, root->getRight()->getRight()->getRight());
	EXPECT_EQ(9, root->getRight()->getRight()->getRight()->getKey());
	delete spt;
}

/**
checks that you do not use findMin in delete (8 should be removed, not 9)
*/
TEST_F(SplayTest, Test_PiazzaDeleteNoFindMax)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(4, 1.0));
	spt->insert(std::make_pair(5, 1.0));
	spt->insert(std::make_pair(8, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(3, 1.0));
	spt->insert(std::make_pair(7, 1.0));

	spt->deleteMaxLeaf();

	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(9, root->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(7, root->getLeft()->getKey());

	ASSERT_EQ(nullptr, root->getRight());
	ASSERT_EQ(nullptr, root->getLeft()->getRight());

	ASSERT_NE(nullptr, root->getLeft()->getLeft());
	EXPECT_EQ(3, root->getLeft()->getLeft()->getKey()); 

	ASSERT_NE(nullptr, root->getLeft()->getLeft()->getRight());
	EXPECT_EQ(5, root->getLeft()->getLeft()->getRight()->getKey());
	delete spt;
}


/**
checks that you do not add a node with same key twice + splay a node
of repeat key found to top
*/
TEST_F(SplayTest, Test_PiazzaInsertDuplicate)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(4, 1.0));
	spt->insert(std::make_pair(1, 1.0));

	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());

	ASSERT_EQ(nullptr, root->getLeft());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(4, root->getRight()->getKey());
	delete spt;
}


/**
checks that you find last element, even if not leaf (should be 9 when finding 10)
*/
TEST_F(SplayTest, Test1_PiazzaNoFind)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(4, 1.0));
	spt->insert(std::make_pair(5, 1.0));
	spt->insert(std::make_pair(8, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(3, 1.0));
	spt->insert(std::make_pair(7, 1.0));

	SplayTree<int, double>::iterator it = spt->find(10);

	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(9, root->getKey());

	ASSERT_EQ(spt->end(), it);

	delete spt;
}

/**
checks that you find last element, if leaf (should be 5 when finding 6)
*/
TEST_F(SplayTest, Test2_PiazzaNoFind)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));
	spt->insert(std::make_pair(4, 1.0));
	spt->insert(std::make_pair(5, 1.0));
	spt->insert(std::make_pair(8, 1.0));
	spt->insert(std::make_pair(9, 1.0));
	spt->insert(std::make_pair(3, 1.0));
	spt->insert(std::make_pair(7, 1.0));

	SplayTree<int, double>::iterator it = spt->find(6);

	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(5, root->getKey());

	ASSERT_EQ(spt->end(), it);
	delete spt;
}

/**
checks that you find root
*/
TEST_F(SplayTest, Test1_PiazzaFindRoot)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));

	SplayTree<int, double>::iterator it = spt->find(1);
	ASSERT_NE(spt->end(), it);
	EXPECT_EQ(1, (*it).first);
	delete spt;
}

/**
checks that you find root
*/
TEST_F(SplayTest, Test2_PiazzaFindRoot)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	spt->insert(std::make_pair(1, 1.0));

	SplayTree<int, double>::iterator it = spt->find(100);

	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(1, root->getKey());

	ASSERT_EQ(spt->end(), it);
	delete spt;
}


/*
Checks that end iterator returned if empty tree
*/
TEST_F(SplayTest, Test_PiazzaEmptyFind)
{
	InheritedBST<int, double> * spt = new InheritedBST<int, double>();
	SplayTree<int, double>::iterator it = spt->find(10);
	ASSERT_EQ(it, spt->end());
	delete spt;
}

/*
Checks cache miss does not occur if element is already in tree
*/
TEST_F(SplayTest, Test_PiazzaCacheMiss){
	InheritedLRU<int, double> * spt = new InheritedLRU<int, double>(3);

	spt->put(std::make_pair(1, 1.0));
	spt->put(std::make_pair(2, 1.0));
	spt->put(std::make_pair(3, 1.0));

	spt->find(2);
	spt->put(std::make_pair(2,1.0));

	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(1, root->getLeft()->getKey());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(3, root->getRight()->getKey());
	delete spt;
}

/*
Checks error is thrown by get if key not in tree
*/
TEST_F(SplayTest, Test_PiazzaThrowError){
	InheritedLRU<int, double> * spt = new InheritedLRU<int, double>(3);

	spt->put(std::make_pair(1, 1.0));
	try{
		spt->get(2);
		std::string result = "uncaught error :(";
		ASSERT_EQ("Caught error", result);
	}catch(std::logic_error &e){}
	delete spt;
}


/*
Checks element is removed if capacity hit
*/
TEST_F(SplayTest, Test_PiazzaRemove){
	InheritedLRU<int, double> * spt = new InheritedLRU<int, double>(1);

	spt->put(std::make_pair(1, 1.0));
	spt->put(std::make_pair(2, 1.0));
	Node<int, double>* root = spt->getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());

	ASSERT_EQ(nullptr, root->getLeft());
	ASSERT_EQ(nullptr, root->getRight());
	delete spt;
}