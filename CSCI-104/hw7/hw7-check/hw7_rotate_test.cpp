#include "../rotateBST.h"
#include "gtest/gtest.h"
#include <random>
#include <algorithm>


template<typename Key, typename Value>
class InheritedRotate;

using StressTreeType = InheritedRotate<std::mt19937::result_type, int>;

template<typename Key, typename Value>
class InheritedRotate : public rotateBST<Key, Value>
{
public:
	void leftRotateRoot() { this->leftRotate(this->mRoot); }
	void rightRotateRoot() { this->rightRotate(this->mRoot); }
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

class RotateTest : public testing::Test 
{
protected:
	void simpleTreeCheck(Node<int, double>* root);
	void stressTestTransform(size_t size, uint seed);
	void redirectOutput(std::ostream& output, 
		void (*f)(const StressTreeType&),
		const StressTreeType& t);
};

void printTree(const StressTreeType& t)
{
	t.print();
}

void RotateTest::simpleTreeCheck(Node<int, double>* root)
{
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(1, root->getLeft()->getKey());
	EXPECT_EQ(root, root->getLeft()->getParent());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(3, root->getRight()->getKey());
	EXPECT_EQ(root, root->getRight()->getParent());
}

void RotateTest::stressTestTransform(size_t size, uint seed)
{
	std::mt19937 g(seed);
	std::vector<decltype(g)::result_type> v;
	StressTreeType t1;
	StressTreeType t2;
	for (size_t i = 0; i < size; ++i)
	{
		decltype(g)::result_type k = g();
		t1.insert(std::make_pair(k, 0));
		v.push_back(k);
	}

	std::shuffle(v.begin(), v.end(), g);
	for (size_t i = 0; i < v.size(); ++i)
	{
		t2.insert(std::make_pair(v[i], 0));
	}

	t1.transform(t2);
	std::ostringstream p1, p2;
	redirectOutput(p1, &printTree, t1);
	redirectOutput(p2, &printTree, t2);
	EXPECT_EQ(p1.str(), p2.str());
}

void RotateTest::redirectOutput(std::ostream& output, 
	void (*f)(const StressTreeType&),
	const StressTreeType& t)
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::cout.rdbuf(output.rdbuf());
	(*f)(t);
	std::cout.rdbuf(oldCout);
}

TEST_F(RotateTest, Test1_LeftRotate) 
{
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);

	bst.leftRotateRoot();
	root = bst.getRoot();
	simpleTreeCheck(root);
}

TEST_F(RotateTest, Test2_RightRotate) 
{
	InheritedRotate<int, double> bst;
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	Node<int, double>* root = bst.getRoot();
	ASSERT_NE(nullptr, root);

	bst.rightRotateRoot();
	root = bst.getRoot();
	simpleTreeCheck(root);
}

TEST_F(RotateTest, Test3_Transform) 
{
	InheritedRotate<int, int> t1, t2;
	t1.insert(std::make_pair(2, 1));
	t1.insert(std::make_pair(1, 1));
	t1.insert(std::make_pair(3, 1));
	t2.insert(std::make_pair(3, 2));
	t2.insert(std::make_pair(2, 2));
	t2.insert(std::make_pair(1, 2));
	t1.transform(t2);

	EXPECT_EQ(2, t2.height());
	EXPECT_EQ(true, t2.isBalanced());

	Node<int, int>* root = t2.getRoot();
	ASSERT_NE(nullptr, root);
	EXPECT_EQ(2, root->getKey());
	EXPECT_EQ(2, root->getValue());

	ASSERT_NE(nullptr, root->getRight());
	EXPECT_EQ(3, root->getRight()->getKey());
	EXPECT_EQ(2, root->getRight()->getValue());

	ASSERT_NE(nullptr, root->getLeft());
	EXPECT_EQ(1, root->getLeft()->getKey());
	EXPECT_EQ(2, root->getLeft()->getValue());
}

TEST_F(RotateTest, Stress1_Transform1000) 
{
	stressTestTransform(100, 103);
}