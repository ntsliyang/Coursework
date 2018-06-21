#include "bst_gtest_class.h"

TEST_F(BSTTest, Test28_CompareByStringKey) 
{
	using Key = std::string;
	using Value = int;
	InsSeq<Key, Value> ins{
		std::make_pair("a", 9),
		std::make_pair("b", 8),
		std::make_pair("c", 7),
		std::make_pair("d", 6),
		std::make_pair("e", 5),
		std::make_pair("f", 4),
		std::make_pair("g", 3),
		std::make_pair("h", 2),
		std::make_pair("i", 1),
		std::make_pair("j", 0),
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{"a", 9, 10, false, true},
		NodeValidation<Key, Value>{"b", 8, 9, false, true},
		NodeValidation<Key, Value>{"c", 7, 8, false, true},
		NodeValidation<Key, Value>{"d", 6, 7, false, true},
		NodeValidation<Key, Value>{"e", 5, 6, false, true},
		NodeValidation<Key, Value>{"f", 4, 5, false, true},
		NodeValidation<Key, Value>{"g", 3, 4, false, true},
		NodeValidation<Key, Value>{"h", 2, 3, false, true},
		NodeValidation<Key, Value>{"i", 1, 2, false, true},
		NodeValidation<Key, Value>{"j", 0, 1, false, false},
	};

	InheritedBST<Key, Value> bst;
	InsertInTree(bst, ins);
}