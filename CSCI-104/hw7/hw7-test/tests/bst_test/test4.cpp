#include "bst_gtest_class.h"

TEST_F(BSTTest, Test4_InsertThreeLeftLL) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(3, 3.0),
		std::make_pair(2, 2.0),
		std::make_pair(1, 1.0),
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{3, 3.0, 3, true, false},
		NodeValidation<Key, Value>{2, 2.0, 2, true, false},
		NodeValidation<Key, Value>{1, 1.0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, false);
}