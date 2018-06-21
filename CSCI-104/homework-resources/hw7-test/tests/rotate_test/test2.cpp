#include "rotate_gtest_class.h"

TEST_F(RotateTest, Test2_RightRotateRoot) 
{
	using Key = int;
	using Value = double;
	InsSeq<Key, Value> ins{
		std::make_pair(2, 2.0),
		std::make_pair(1, 1.0),
	};

	NodeSeq<Key, Value> seq{
		NodeValidation<Key, Value>{1, 1.0, 0, false, true},
		NodeValidation<Key, Value>{2, 2.0, 0, false, false},
	};

	Path path{};

	InheritedRotate<Key, Value> bst;
	InsertInTree(bst, ins);
	bst.exposedRightRotate(TraversePath(bst, path));
	TreeStructureCheck(bst.getRoot(), seq, false);
}