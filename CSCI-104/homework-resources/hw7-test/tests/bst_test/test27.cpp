#include "bst_gtest_class.h"

TEST_F(BSTTest, Test27_FindSmallestNode) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(5, 5.0),
		std::make_pair(3, 3.0),
		std::make_pair(0, 0.0),
		std::make_pair(2, 2.0),
		std::make_pair(1, 1.0),
		std::make_pair(4, 4.0),
		std::make_pair(9, 9.0),
		std::make_pair(8, 8.0),
		std::make_pair(6, 6.0),
		std::make_pair(7, 7.0),
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	CheckGetSmallest(bst, &ins[2]);
}