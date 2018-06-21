#include "bst_gtest_class.h"

TEST_F(BSTTest, Test18_RemoveFive) 
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

	RemSeq<Key> rem{
		3,
		2,
		6,
		9,
		5,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{4, 4.0, 3, true, true},
		NodeValidation<Key, Value>{1, 1.0, 2, true, false},
		NodeValidation<Key, Value>{0, 0.0, 1, false, false},
		NodeValidation<Key, Value>{8, 8.0, 2, true, false},
		NodeValidation<Key, Value>{7, 7.0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, true);
}