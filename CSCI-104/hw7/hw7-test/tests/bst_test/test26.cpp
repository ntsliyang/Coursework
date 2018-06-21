#include "bst_gtest_class.h"

TEST_F(BSTTest, Test26_InternalFindNonexisting) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(5, 5.0),
		std::make_pair(0, 0.0),
		std::make_pair(3, 3.0),
		std::make_pair(2, 2.0),
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	CheckInternalFind(bst, 1, static_cast<const Value*>(nullptr));
}