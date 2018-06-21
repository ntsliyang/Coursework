#include "splay_gtest_header.h"

TEST_F(SplayTest, Test23_RemoveTwoChildrenSplayPred)
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(1, 1.0),
		std::make_pair(5, 5.0),
		std::make_pair(9, 9.0),
		std::make_pair(8, 8.0),
		std::make_pair(3, 3.0),
	};

	RemSeq<Key> rem{
		8,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{5, 5.0, true, true},
		NodeValidation<Key, Value>{3, 3.0, true, false},
		NodeValidation<Key, Value>{1, 1.0, false, false},
		NodeValidation<Key, Value>{9, 9.0, false, false},
	};

	InheritedSplay<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
}