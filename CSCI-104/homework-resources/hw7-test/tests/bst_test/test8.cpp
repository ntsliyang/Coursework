#include "bst_gtest_class.h"

TEST_F(BSTTest, Test8_InsertDuplicate) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(2, 2.0),
		std::make_pair(1, 1.0),
		std::make_pair(3, 3.0),
		std::make_pair(2, 20.0),
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{2, 2.0, 2, true, true},
		NodeValidation<Key, Value>{1, 1.0, 1, false, false},
		NodeValidation<Key, Value>{3, 3.0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, true);
}