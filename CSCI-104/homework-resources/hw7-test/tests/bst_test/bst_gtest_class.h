#include "../../../bst.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

template<typename Key, typename Value>
class InheritedBST : public BinarySearchTree<Key, Value>
{
public:
	Node<Key, Value>* getRoot() { return this->mRoot; }
	Node<Key, Value>* exposedInternalFind(const Key& k) const { return this->internalFind(k); }
	Node<Key, Value>* exposedGetSmallest() const { return this->getSmallestNode(); }
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

template<typename Key>
using RemSeq = std::vector<Key>;

template<typename Key, typename Value>
using NodeSeq = std::vector<NodeValidation<Key, Value>>;

template<typename Key, typename Value>
using NodeSeqIter = typename std::vector<NodeValidation<Key, Value>>::const_iterator;

using StressKey = int;
using StressValue = int;
using StressBST = InheritedBST<StressKey, StressValue>;
using StressKeySeq = std::vector<StressKey>;

class BSTTest : public testing::Test 
{
protected:
	template<typename Key, typename Value>
	void CheckHeightBalance(InheritedBST<Key, Value>& bst, bool balanced);

	template<typename Key, typename Value>
	void CheckInternalFind(InheritedBST<Key, Value>& bst, const Key& key, const Value* value);

	template<typename Key, typename Value>
	void CheckGetSmallest(InheritedBST<Key, Value>& bst, const std::pair<Key, Value>* exp);

	template<typename Key, typename Value>
	void InsertInTree(BinarySearchTree<Key, Value>& bst, const InsSeq<Key, Value>& ins);

	template<typename Key, typename Value>
	void RemoveFromTree(BinarySearchTree<Key, Value>& bst, const RemSeq<Key>& rem);

	template<typename Key, typename Value>
	void TreeStructureCheck(Node<Key, Value>* root, const NodeSeq<Key, Value>& cmp);

	template<typename Key, typename Value>
	void PreOrderTraversal(Node<Key, Value>* root, NodeSeqIter<Key, Value>& cmp, NodeSeqIter<Key, Value> end);

	void InsertFull(StressBST& bst, StressKey height);
	void StressHeight(StressBST& bst);
	void StressInsert(StressBST& bst);
	void StressRemove(StressBST& bst);
	void StressInternalFind(StressBST& bst);
	void StressGetSmallest(StressBST& bst);
	void CheckRuntime(std::clock_t times[4], double ignoreLessThan, double scalingFactor);

protected:
	StressBST mBST1;
	StressBST mBST2;
	StressBST mBST3;
	const size_t mStressSize = 10000;
};

template<typename Key, typename Value>
void BSTTest::CheckHeightBalance(InheritedBST<Key, Value>& bst, bool balanced)
{
	Node<Key, Value>* root = bst.getRoot();
	if (root == nullptr)
	{
		EXPECT_EQ(0, bst.height());
		EXPECT_EQ(true, bst.isBalanced());
	}
	else
	{
		EXPECT_EQ(root->getHeight(), bst.height());
		EXPECT_EQ(balanced, bst.isBalanced());
	}
}

template<typename Key, typename Value>
void BSTTest::CheckInternalFind(InheritedBST<Key, Value>& bst, const Key& key, const Value* value)
{
	Node<Key, Value>* found = bst.exposedInternalFind(key);
	if (value == nullptr)
	{
		EXPECT_EQ(nullptr, found);
	}
	else
	{
		ASSERT_NE(nullptr, found);
		EXPECT_EQ(key, found->getKey());
		EXPECT_EQ(*value, found->getValue());
	}
}

template<typename Key, typename Value>
void BSTTest::CheckGetSmallest(InheritedBST<Key, Value>& bst, const std::pair<Key, Value>* exp)
{
	Node<Key, Value>* smallest = bst.exposedGetSmallest();
	if (exp == nullptr)
	{
		EXPECT_EQ(nullptr, smallest);
	}
	else
	{
		ASSERT_NE(nullptr, smallest);
		EXPECT_EQ(exp->first, smallest->getKey());
		EXPECT_EQ(exp->second, smallest->getValue());
	}
}

template<typename Key, typename Value>
void BSTTest::InsertInTree(BinarySearchTree<Key, Value>& bst, const InsSeq<Key, Value>& ins)
{
	for (const auto& kv : ins)
	{
		bst.insert(kv);
	}
}

template<typename Key, typename Value>
void BSTTest::RemoveFromTree(BinarySearchTree<Key, Value>& bst, const RemSeq<Key>& rem)
{
	for (const auto& key : rem)
	{
		bst.remove(key);
	}
}

template<typename Key, typename Value>
void BSTTest::TreeStructureCheck(Node<Key, Value>* root, const NodeSeq<Key, Value>& seq)
{
	if (root != nullptr)
	{
		EXPECT_EQ(nullptr, root->getParent());
	}
	NodeSeqIter<Key, Value> src = seq.begin();
	NodeSeqIter<Key, Value> end = seq.end();
	PreOrderTraversal(root, src, end);
	// Unless tree is empty, src should point at last element.
	EXPECT_TRUE(root == nullptr || src != end);
	if (src != end)
	{
		++src;
		EXPECT_EQ(src, end); // one past last element should be end.
	}
}

template<typename Key, typename Value>
void BSTTest::PreOrderTraversal(Node<Key, Value>* cmp, NodeSeqIter<Key, Value>& src, NodeSeqIter<Key, Value> end)
{
	if (src == end)
	{ // tree should not have more nodes than sequence
		EXPECT_EQ(cmp, nullptr);
	}
	else if (cmp != nullptr)
	{
		EXPECT_EQ(src->getKey(), cmp->getKey());
		EXPECT_EQ(src->getValue(), cmp->getValue());
		EXPECT_EQ(src->getHeight(), cmp->getHeight());
		Node<Key, Value>* left = cmp->getLeft();
		Node<Key, Value>* right = cmp->getRight();
		EXPECT_EQ(src->hasLeft(), left != nullptr);
		EXPECT_EQ(src->hasRight(), right != nullptr);
		if (left != nullptr)
		{
			EXPECT_EQ(cmp, left->getParent());
			PreOrderTraversal(left, ++src, end);
		}
		if (right != nullptr)
		{
			EXPECT_EQ(cmp, right->getParent());
			PreOrderTraversal(right, ++src, end);
		}
	}
}

void BSTTest::InsertFull(StressBST& bst, StressKey height)
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

void BSTTest::StressHeight(StressBST& bst)
{
	for (size_t i = 0; i < mStressSize; ++i)
	{
		bst.height();
	}
}

void BSTTest::StressInsert(StressBST& bst)
{
	for (size_t i = 0; i < mStressSize; ++i)
	{
		bst.insert(std::make_pair(static_cast<StressKey>(-1), 0));
	}
}

void BSTTest::StressRemove(StressBST& bst)
{
	for (size_t i = 0; i < mStressSize; ++i)
	{
		bst.remove(-1);
	}
}

void BSTTest::StressInternalFind(StressBST& bst)
{
	for (size_t i = 0; i < mStressSize; ++i)
	{
		bst.exposedInternalFind(-1);
	}
}

void BSTTest::StressGetSmallest(StressBST& bst)
{
	for (size_t i = 0; i < mStressSize; ++i)
	{
		bst.exposedGetSmallest();
	}
}

void BSTTest::CheckRuntime(std::clock_t times[4], double ignoreLessThan, double scalingFactor)
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