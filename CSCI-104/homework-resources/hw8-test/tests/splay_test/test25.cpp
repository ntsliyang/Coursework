#include "splay_gtest_header.h"

TEST_F(SplayTest, Test25_RemoveRecursiveSplay)
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(5, 5.0),
		std::make_pair(6, 6.0),
		std::make_pair(3, 3.0),
		std::make_pair(4, 4.0),
		std::make_pair(12, 12.0),
		std::make_pair(16, 16.0),
		std::make_pair(11, 11.0),
		std::make_pair(13, 13.0),
		std::make_pair(8, 8.0),
		std::make_pair(10, 10.0),
		std::make_pair(9, 9.0),
		std::make_pair(15, 15.0),
		std::make_pair(24, 24.0),
		std::make_pair(22, 22.0),
		std::make_pair(28, 28.0),
		std::make_pair(23, 23.0),
	};

	RemSeq<Key> rem{
		11,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{10, 10.0, true, true},
		NodeValidation<Key, Value>{9, 9.0, true, false},
		NodeValidation<Key, Value>{8, 8.0, true, false},
		NodeValidation<Key, Value>{6, 6.0, true, false},
		NodeValidation<Key, Value>{4, 4.0, true, true},
		NodeValidation<Key, Value>{3, 3.0, false, false},
		NodeValidation<Key, Value>{5, 5.0, false, false},
		NodeValidation<Key, Value>{23, 23.0, true, true},
		NodeValidation<Key, Value>{16, 16.0, true, true},
		NodeValidation<Key, Value>{15, 15.0, true, false},
		NodeValidation<Key, Value>{13, 13.0, true, false},
		NodeValidation<Key, Value>{12, 12.0, false, false},
		NodeValidation<Key, Value>{22, 22.0, false, false},
		NodeValidation<Key, Value>{28, 28.0, true, false},
		NodeValidation<Key, Value>{24, 24.0, false, false},
	};

	InheritedSplay<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
}