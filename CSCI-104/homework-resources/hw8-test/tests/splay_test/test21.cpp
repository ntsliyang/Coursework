#include "splay_gtest_header.h"

TEST_F(SplayTest, Test21_RemoveLeafLeftChild)
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(2, 2.0),
		std::make_pair(1, 1.0),
		std::make_pair(3, 3.0),
	};

	RemSeq<Key> rem{
		1,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{2, 2.0, false, true},
		NodeValidation<Key, Value>{3, 3.0, false, false},
	};

	InheritedSplay<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
}