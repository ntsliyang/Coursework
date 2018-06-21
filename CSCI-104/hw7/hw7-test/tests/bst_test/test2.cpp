#include "bst_gtest_class.h"

TEST_F(BSTTest, Test2_InsertOne) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(1, 1.0),
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{1, 1.0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, true);
}