#include "bst_gtest_class.h"

TEST_F(BSTTest, Test20_MixedInsertRemove) 
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
	RemSeq<Key> rem1{
		5,
	};
	InsSeq<Key, Value> ins2{
		std::make_pair(4, 4.0),
		std::make_pair(5, 5.0),
	};
	RemSeq<Key> rem2{
		3,
		2,
		4,
		9,
		5,
		0,
		7,
	};
	InsSeq<Key, Value> ins3{
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
	RemoveFromTree(bst, rem1);
	InsertInTree(bst, ins2);
	RemoveFromTree(bst, rem2);
	InsertInTree(bst, ins3);
	TreeStructureCheck(bst.getRoot(), seq);
	CheckHeightBalance(bst, false);
}