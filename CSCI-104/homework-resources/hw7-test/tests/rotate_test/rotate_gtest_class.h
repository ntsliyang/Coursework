#include "../../../rotateBST.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

template<typename Key, typename Value>
class InheritedRotate : public rotateBST<Key, Value>
{
public:
	void exposedLeftRotate(Node<Key, Value>* node) { this->leftRotate(node); }
	void exposedRightRotate(Node<Key, Value>* node) { this->rightRotate(node); }
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

template<typename Key, typename Value>
struct NodeValidation
{
	Key mKey;
	Value mValue;
	int mHeight;
	bool mHasLeft;
	bool mHasRight;

	const Key& getKey() const { return mKey; }
	const Value& getValue() const { return mValue; }
	int getHeight() const { return mHeight; }
	bool hasLeft() const { return mHasLeft; }
	bool hasRight() const { return mHasRight; }
};

template<typename Key, typename Value>
using InsSeq = std::vector<std::pair<Key, Value>>;

template<typename Key, typename Value>
using NodeSeq = std::vector<NodeValidation<Key, Value>>;

template<typename Key, typename Value>
using NodeSeqIter = typename std::vector<NodeValidation<Key, Value>>::const_iterator;

using Path = std::vector<bool>;

using StressKey = int;
using StressValue = int;
using StressBST = InheritedRotate<StressKey, StressValue>;

class RotateTest : public testing::Test 
{
protected:
	template<typename Key, typename Value>
	Node<Key, Value>* TraversePath(InheritedRotate<Key, Value>& bst, const Path& path);

	template<typename Key, typename Value>
	void InsertInTree(BinarySearchTree<Key, Value>& bst, const InsSeq<Key, Value>& ins);

	template<typename Key, typename Value>
	void TreeStructureCheck(
		Node<Key, Value>* root,
		const NodeSeq<Key, Value>& cmp,
		bool compareHeight);
	template<typename Key, typename Value>

	void PreOrderTraversal(
		Node<Key, Value>* root,
		NodeSeqIter<Key, Value>& cmp,
		NodeSeqIter<Key, Value> end,
		bool compareHeight);

	template<typename Key, typename Value>
	void CompareTreeStructure(Node<Key, Value>* r1, Node<Key, Value>* r2);

	void InsertFull(StressBST& bst, StressKey height);
	void InsertRandom(
		StressBST& bst,
		size_t size,
		std::mt19937& g,
		InsSeq<StressKey, StressValue>& seq);
	void CheckRuntime(std::clock_t times[4], double ignoreLessThan, double scalingFactor);

protected:
	StressBST mBST1;
	StressBST mBST2;
	StressBST mBST3;
};

template<typename Key, typename Value>
Node<Key, Value>* RotateTest::TraversePath(InheritedRotate<Key, Value>& bst, const Path& path)
{
	Node<Key, Value>* curr = bst.getRoot();
	for (bool left : path)
	{
		EXPECT_NE(nullptr, curr);
		if (curr == nullptr)
		{
			break;
		}
		if (left)
		{
			curr = curr->getLeft();
		}
		else
		{
			curr = curr->getRight();
		}
	}
	EXPECT_NE(nullptr, curr);
	return curr;
}

template<typename Key, typename Value>
void RotateTest::InsertInTree(BinarySearchTree<Key, Value>& bst, const InsSeq<Key, Value>& ins)
{
	for (const auto& kv : ins)
	{
		bst.insert(kv);
	}
}

template<typename Key, typename Value>
void RotateTest::TreeStructureCheck(
		Node<Key, Value>* root,
		const NodeSeq<Key, Value>& seq,
		bool compareHeight)
{
	if (root != nullptr)
	{
		EXPECT_EQ(nullptr, root->getParent());
	}
	NodeSeqIter<Key, Value> src = seq.begin();
	NodeSeqIter<Key, Value> end = seq.end();
	PreOrderTraversal(root, src, end, compareHeight);
	// Unless tree is empty, src should point at last element.
	EXPECT_TRUE(root == nullptr || src != end);
	if (src != end)
	{
		++src;
		EXPECT_EQ(src, end); // one past last element should be end.
	}
}

template<typename Key, typename Value>
void RotateTest::PreOrderTraversal(
		Node<Key, Value>* cmp,
		NodeSeqIter<Key, Value>& src,
		NodeSeqIter<Key, Value> end,
		bool compareHeight)
{
	if (src == end)
	{ // tree should not have more nodes than sequence
		EXPECT_EQ(cmp, nullptr);
	}
	else if (cmp != nullptr)
	{
		EXPECT_EQ(src->getKey(), cmp->getKey());
		EXPECT_EQ(src->getValue(), cmp->getValue());
		if (compareHeight)
		{
			EXPECT_EQ(src->getHeight(), cmp->getHeight());		
		}
		Node<Key, Value>* left = cmp->getLeft();
		Node<Key, Value>* right = cmp->getRight();
		EXPECT_EQ(src->hasLeft(), left != nullptr);
		EXPECT_EQ(src->hasRight(), right != nullptr);
		if (left != nullptr)
		{
			EXPECT_EQ(cmp, left->getParent());
			PreOrderTraversal(left, ++src, end, compareHeight);
		}
		if (right != nullptr)
		{
			EXPECT_EQ(cmp, right->getParent());
			PreOrderTraversal(right, ++src, end, compareHeight);
		}
	}
}

template<typename Key, typename Value>
void RotateTest::CompareTreeStructure(Node<Key, Value>* r1, Node<Key, Value>* r2)
{
	if (r1 != nullptr && r2 != nullptr)
	{
		EXPECT_EQ(r1->getKey(), r2->getKey());
		EXPECT_EQ(r1->getHeight(), r2->getHeight());
		CompareTreeStructure(r1->getLeft(), r2->getLeft());
		CompareTreeStructure(r1->getRight(), r2->getRight());
	}
	else
	{
		EXPECT_EQ(r1, r2);
	}
}

void RotateTest::InsertFull(StressBST& bst, StressKey height)
{
	for (StressKey h = 0; h < height; ++h)
	{
		StressKey start = 1 << (height - h - 1);
		StressKey inc = start * 2;
		StressKey count = 1 << h;
		for (StressKey i = 0; i < count; ++i)
		{
			bst.insert(std::make_pair(start, 0));
			start += inc;
		}
	}
}

void RotateTest::InsertRandom(
	StressBST& bst,
	size_t size,
	std::mt19937& g,
	InsSeq<StressKey, StressValue>& seq)
{
	for (size_t i = 0; i < size; ++i)
	{
		seq.push_back(std::make_pair(static_cast<StressKey>(g()), 0));
		bst.insert(seq.back());
	}
}

void RotateTest::CheckRuntime(std::clock_t times[4], double ignoreLessThan, double scalingFactor)
{
	double elapsed1 = double(times[1] - times[0]) / CLOCKS_PER_SEC * 1000;
  	double elapsed2 = double(times[2] - times[1]) / CLOCKS_PER_SEC * 1000;
  	double elapsed3 = double(times[3] - times[2]) / CLOCKS_PER_SEC * 1000;

  	std::cout << "bst1: " << elapsed1 << std::endl;
  	std::cout << "bst2: " << elapsed2 << std::endl;
  	std::cout << "bst3: " << elapsed3 << std::endl;

  	double scale1 = elapsed2 / elapsed1;
  	double scale2 = elapsed3 / elapsed2;
  	EXPECT_TRUE(elapsed1 < ignoreLessThan || scale1 < scalingFactor);
  	EXPECT_TRUE(elapsed2 < ignoreLessThan || scale2 < scalingFactor);
}