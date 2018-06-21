#include "splay_gtest_header.h"

TEST_F(SplayTest, Test24_RemoveRecursiveSplay)
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(1, 1.0),
		std::make_pair(5, 5.0),
		std::make_pair(9, 9.0),
		std::make_pair(8, 8.0),
		std::make_pair(4, 4.0),
		std::make_pair(0, 0.0),
		std::make_pair(3, 3.0),
		std::make_pair(7, 7.0),
		std::make_pair(15, 15.0),
		std::make_pair(12, 12.0),
		std::make_pair(10, 10.0),
		std::make_pair(11, 11.0),
	};

	RemSeq<Key> rem{
		4,
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{3, 3.0, true, true},
		NodeValidation<Key, Value>{0, 0.0, false, true},
		NodeValidation<Key, Value>{1, 1.0, false, false},
		NodeValidation<Key, Value>{10, 10.0, true, true},
		NodeValidation<Key, Value>{7, 7.0, true, true},
		NodeValidation<Key, Value>{5, 5.0, false, false},
		NodeValidation<Key, Value>{9, 9.0, true, false},
		NodeValidation<Key, Value>{8, 8.0, false, false},
		NodeValidation<Key, Value>{11, 11.0, false, true},
		NodeValidation<Key, Value>{12, 12.0, false, true},
		NodeValidation<Key, Value>{15, 15.0, false, false},
	};

	InheritedSplay<Key, Value> bst;
	InsertInTree(bst, ins);
	RemoveFromTree(bst, rem);
	TreeStructureCheck(bst.getRoot(), seq);
}