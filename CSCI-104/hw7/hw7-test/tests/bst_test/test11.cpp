#include "bst_gtest_class.h"

TEST_F(BSTTest, Test11_RemoveLeafLeftChild) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(4, 4.0),
		std::make_pair(2, 2.0),
		std::make_pair(1, 1.0),
		std::make_pair(3, 3.0)
	};

	RemSeq<Key> rem{
		1,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{4, 4.0, 3, true, false},
		NodeValidation<Key, Value>{2, 2.0, 2, false, true},
		NodeValidation<Key, Value>{3, 3.0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, false);
}