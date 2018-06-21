#include "bst_gtest_class.h"

TEST_F(BSTTest, Test21_InsertAfterClear) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins1{
		std::make_pair(5, 5.0),
		std::make_pair(3, 3.0),
		std::make_pair(2, 2.0),
		std::make_pair(0, 0.0),
		std::make_pair(9, 9.0),
		std::make_pair(7, 7.0),
	};
	InsSeq<Key, Value> ins2{
		std::make_pair(8, 8.0),
		std::make_pair(1, 1.0),
		std::make_pair(5, 100.0),
		std::make_pair(7, 700.0),
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{8, 8.0, 4, true, false},
		NodeValidation<Key, Value>{1, 1.0, 3, false, true},
		NodeValidation<Key, Value>{5, 100.0, 2, false, true},
		NodeValidation<Key, Value>{7, 700.0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins1);
	bst.clear();
	InsertInTree(bst, ins2);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, false);
}