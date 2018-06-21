#include "splay_gtest_header.h"

TEST_F(SplayTest, Test26_RemoveNonExisting)
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(2, 2.0),
		std::make_pair(1, 1.0),
		std::make_pair(6, 6.0),
		std::make_pair(4, 4.0),
		std::make_pair(0, 0.0),
	};

	RemSeq<Key> rem{
		7,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{6, 6.0, true, false},
		NodeValidation<Key, Value>{4, 4.0, true, false},
		NodeValidation<Key, Value>{0, 0.0, false, true},
		NodeValidation<Key, Value>{1, 1.0, false, true},
		NodeValidation<Key, Value>{2, 2.0, false, false},
	};

	InheritedSplay<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
}