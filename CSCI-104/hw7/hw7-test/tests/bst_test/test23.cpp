#include "bst_gtest_class.h"

TEST_F(BSTTest, Test23_InternalFindLeftTraversal) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(5, 5.0),
		std::make_pair(3, 3.0),
		std::make_pair(2, 2.0),
		std::make_pair(0, 42.0),
		std::make_pair(7, 7.0),
		std::make_pair(8, 8.0),
		std::make_pair(9, 9.0),
	};
	std::pair<Key, Value> exp = ins[3];

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	CheckInternalFind(bst, exp.first, &exp.second);
}