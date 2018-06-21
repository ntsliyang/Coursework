#include "bst_gtest_class.h"

TEST_F(BSTTest, Test19_RemoveNonexisting) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(6, 6.0),
		std::make_pair(2, 2.0),
		std::make_pair(8, 8.0),
	};

	RemSeq<Key> rem{
		9,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{6, 6.0, 2, true, true},
		NodeValidation<Key, Value>{2, 2.0, 1, false, false},
		NodeValidation<Key, Value>{8, 8.0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, true);
}