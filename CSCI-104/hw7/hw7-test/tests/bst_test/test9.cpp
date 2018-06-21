#include "bst_gtest_class.h"

TEST_F(BSTTest, Test9_RemoveOnlyNode) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(1, 1.0),
	};

	RemSeq<Key> rem{
		1,
	};

	NodeSeq<Key, Value> seq{
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, false);
}