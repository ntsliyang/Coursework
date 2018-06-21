#include "splay_gtest_header.h"

TEST_F(SplayTest, Test15_FindMixedSequence)
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(2, 2.0),
		std::make_pair(5, 5.0),
		std::make_pair(6, 6.0),
		std::make_pair(1, 1.0),
		std::make_pair(9, 9.0),
		std::make_pair(7, 7.0),
		std::make_pair(8, 8.0),
	};
	std::pair<Key, Value> exp(5, 5.0);

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{5, 5.0, true, true},
		NodeValidation<Key, Value>{2, 2.0, true, false},
		NodeValidation<Key, Value>{1, 1.0, false, false},
		NodeValidation<Key, Value>{8, 8.0, true, true},
		NodeValidation<Key, Value>{6, 6.0, false, true},
		NodeValidation<Key, Value>{7, 7.0, false, false},
		NodeValidation<Key, Value>{9, 9.0, false, false},
	};

	InheritedSplay<Key, Value> bst;
	InsertInTree(bst, ins);
	CheckFind(bst, exp.first, &exp.second);
	TreeStructureCheck(bst.getRoot(), seq);
}