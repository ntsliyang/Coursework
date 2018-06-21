#include "../../../splayTree.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

template<typename Key, typename Value>
class InheritedSplay : public SplayTree<Key, Value>
{
public:
	void exposedSplay(Node<Key, Value>* node) { this->splay(node); }
	Node<Key, Value>* getRoot() { return this->mRoot; }
};

template<typename Key, typename Value>
struct NodeValidation
{
	Key mKey;
	Value mValue;
	bool mHasLeft;
	bool mHasRight;

	const Key& getKey() const { return mKey; }
	const Value& getValue() const { return mValue; }
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

using Path = std::vector<bool>;

using StressKey = int;
using StressValue = int;
using StressBST = InheritedSplay<StressKey, StressValue>;

class SplayTest : public testing::Test 
{
protected:
	template<typename Key, typename Value>
	void InsertInTree(InheritedSplay<Key, Value>& bst, const InsSeq<Key, Value>& ins);

	template<typename Key, typename Value>
	void RemoveFromTree(InheritedSplay<Key, Value>& bst, const RemSeq<Key>& rem);

	template<typename Key, typename Value>
	void CheckFind(InheritedSplay<Key, Value>& bst, const Key& key, const Value* value);

	template<typename Key, typename Value>
	void CheckFindMin(InheritedSplay<Key, Value>& bst, const std::pair<Key, Value>* exp);

	template<typename Key, typename Value>
	void CheckFindMax(InheritedSplay<Key, Value>& bst, const std::pair<Key, Value>* exp);

	template<typename Key, typename Value>
	void TreeStructureCheck(Node<Key, Value>* root, const NodeSeq<Key, Value>& cmp);

	template<typename Key, typename Value>
	void PreOrderTraversal(Node<Key, Value>* root, NodeSeqIter<Key, Value>& cmp, NodeSeqIter<Key, Value> end);

	template<typename Key, typename Value>
	void CompareTreeStructure(Node<Key, Value>* r1, Node<Key, Value>* r2);

	void InsertRandom(StressBST& bst, size_t size, std::mt19937& g);
	void FindRandom(StressBST& bst, size_t size, std::mt19937& g);
	void RemoveRandom(StressBST& bst, size_t size, std::mt19937& g);
	void CheckRuntime(std::clock_t times[4], double ignoreLessThan, double scalingFactor);

protected:
	StressBST mBST1;
	StressBST mBST2;
	StressBST mBST3;
	const size_t mStressSize = 1000;
};

template<typename Key, typename Value>
void SplayTest::InsertInTree(InheritedSplay<Key, Value>& bst, const InsSeq<Key, Value>& ins)
{
	for (const auto& kv : ins)
	{
		bst.insert(kv);
	}
}

template<typename Key, typename Value>
void SplayTest::RemoveFromTree(InheritedSplay<Key, Value>& bst, const RemSeq<Key>& rem)
{
	for (const auto& key : rem)
	{
		bst.remove(key);
	}
}

template<typename Key, typename Value>
void SplayTest::CheckFind(InheritedSplay<Key, Value>& bst, const Key& key, const Value* value)
{
	typename InheritedSplay<Key, Value>::iterator found = bst.find(key);
	if (value == nullptr)
	{
		EXPECT_EQ(bst.end(), found);
	}
	else
	{
		ASSERT_NE(bst.end(), found);
		EXPECT_EQ(key, found->first);
		EXPECT_EQ(*value, found->second);
	}
}

template<typename Key, typename Value>
void SplayTest::CheckFindMin(InheritedSplay<Key, Value>& bst, const std::pair<Key, Value>* exp)
{
	typename InheritedSplay<Key, Value>::iterator found = bst.findMin();
	if (exp == nullptr)
	{
		EXPECT_EQ(bst.end(), found);
	}
	else
	{
		ASSERT_NE(bst.end(), found);
		EXPECT_EQ(exp->first, found->first);
		EXPECT_EQ(exp->second, found->second);
	}
}

template<typename Key, typename Value>
void SplayTest::CheckFindMax(InheritedSplay<Key, Value>& bst, const std::pair<Key, Value>* exp)
{
	typename InheritedSplay<Key, Value>::iterator found = bst.findMax();
	if (exp == nullptr)
	{
		EXPECT_EQ(bst.end(), found);
	}
	else
	{
		ASSERT_NE(bst.end(), found);
		EXPECT_EQ(exp->first, found->first);
		EXPECT_EQ(exp->second, found->second);
	}
}

template<typename Key, typename Value>
void SplayTest::TreeStructureCheck(
		Node<Key, Value>* root,
		const NodeSeq<Key, Value>& seq)
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
void SplayTest::PreOrderTraversal(
		Node<Key, Value>* cmp,
		NodeSeqIter<Key, Value>& src,
		NodeSeqIter<Key, Value> end)
{
	if (src == end)
	{ // tree should not have more nodes than sequence
		EXPECT_EQ(nullptr, cmp);
	}
	else if (cmp != nullptr)
	{
		EXPECT_EQ(src->getKey(), cmp->getKey());
		EXPECT_EQ(src->getValue(), cmp->getValue());
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

void SplayTest::InsertRandom(StressBST& bst, size_t size, std::mt19937& g)
{
	for (size_t i = 0; i < size; ++i)
	{
		bst.insert(std::make_pair(static_cast<StressKey>(g()), 0));
	}
}

void SplayTest::FindRandom(StressBST& bst, size_t size, std::mt19937& g)
{
	for (size_t i = 0; i < size; ++i)
	{
		bst.find(static_cast<StressKey>(g()));
	}
}

void SplayTest::RemoveRandom(StressBST& bst, size_t size, std::mt19937& g)
{
	for (size_t i = 0; i < size; ++i)
	{
		bst.remove(static_cast<StressKey>(g()));
	}
}

void SplayTest::CheckRuntime(std::clock_t times[4], double ignoreLessThan, double scalingFactor)
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