#include "bst_gtest_class.h"

TEST_F(BSTTest, Test16_RemoveWithNonLeafPredecessor) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(6, 6.0),
		std::make_pair(10, 10.0),
		std::make_pair(7, 7.0),
		std::make_pair(9, 9.0),
		std::make_pair(8, 8.0),
		std::make_pair(11, 11.0),
	};

	RemSeq<Key> rem{
		10,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{6, 6.0, 4, false, true},
		NodeValidation<Key, Value>{9, 9.0, 3, true, true},
		NodeValidation<Key, Value>{7, 7.0, 2, false, true},
		NodeValidation<Key, Value>{8, 8.0, 1, false, false},
		NodeValidation<Key, Value>{11, 11.0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, false);
}