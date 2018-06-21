#include "bst_gtest_class.h"

TEST_F(BSTTest, Stress1_Height) 
{
	InsertFull(mBST1, 14, mKey1);
	InsertFull(mBST2, 15, mKey1);
	InsertFull(mBST3, 16, mKey3);

	std::clock_t t1 = std::clock();

	EXPECT_EQ(14, mBST1.height());
	std::clock_t t2 = std::clock();

	EXPECT_EQ(15, mBST2.height());
	std::clock_t t3 = std::clock();

	EXPECT_EQ(16, mBST3.height());
	std::clock_t t4 = std::clock();

	CheckRuntime(t1, t2, t3, t4, 5, 2);
}