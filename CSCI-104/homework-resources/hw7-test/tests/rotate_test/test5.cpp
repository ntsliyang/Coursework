#include "rotate_gtest_class.h"

TEST_F(RotateTest, Test5_LeftRotateRightChildOfParent) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(3, 3.0),
		std::make_pair(4, 4.0),
		std::make_pair(5, 5.0),
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{3, 3.0, 0, false, true},
		NodeValidation<Key, Value>{5, 5.0, 0, true, false},
		NodeValidation<Key, Value>{4, 4.0, 0, false, false},
	};

	Path path{false};

	InheritedRotate<Key, Value> bst;
	InsertInTree(bst, ins);
	bst.exposedLeftRotate(TraversePath(bst, path));
	TreeStructureCheck(bst.getRoot(), seq, false);
}