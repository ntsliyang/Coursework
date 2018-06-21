#include "splay_gtest_header.h"

TEST_F(SplayTest, Test22_RemoveLeafRightChild)
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(5, 5.0),
		std::make_pair(6, 6.0),
		std::make_pair(2, 2.0),
		std::make_pair(3, 3.0),
	};

	RemSeq<Key> rem{
		6,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{5, 5.0, true, false},
		NodeValidation<Key, Value>{3, 3.0, true, false},
		NodeValidation<Key, Value>{2, 2.0, false, false},
	};

	InheritedSplay<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
}