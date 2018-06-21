#include "bst_gtest_class.h"

TEST_F(BSTTest, Test1_EmptyTree) 
{
	using Key = int;
	using Value = double;
	InheritedBST<Key, Value> bst;
	EXPECT_EQ(nullptr, bst.getRoot());
	CheckHeightBalance(bst, true);
}