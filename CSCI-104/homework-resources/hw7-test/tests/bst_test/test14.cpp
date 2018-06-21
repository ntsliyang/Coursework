#include "bst_gtest_class.h"

TEST_F(BSTTest, Test14_RemoveWithRightChild) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(4, 4.0),
		std::make_pair(6, 6.0),
		std::make_pair(7, 7.0),
		std::make_pair(8, 8.0),
	};

	RemSeq<Key> rem{
		6,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{4, 4.0, 3, false, true},
		NodeValidation<Key, Value>{7, 7.0, 2, false, true},
		NodeValidation<Key, Value>{8, 8.0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, false);
}