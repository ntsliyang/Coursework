#include "bst_gtest_class.h"

TEST_F(BSTTest, Test25_InternalFindMixedTraversal) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(5, 5.0),
		std::make_pair(0, 0.0),
		std::make_pair(3, 3.0),
		std::make_pair(2, 42.0),
	};
	std::pair<Key, Value> exp = ins.back();

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	CheckInternalFind(bst, exp.first, &exp.second);
}