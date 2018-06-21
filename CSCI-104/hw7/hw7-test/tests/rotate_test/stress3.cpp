#include "rotate_gtest_class.h"

TEST_F(RotateTest, Stress2_SameKeys) 
{
	InsertFull(mBST1, 14);
	InsertFull(mBST2, 15);
	InsertFull(mBST3, 16);

	std::clock_t t1 = std::clock();

	EXPECT_TRUE(mBST1.sameKeys(mBST1));
	std::clock_t t2 = std::clock();

	EXPECT_TRUE(mBST2.sameKeys(mBST2));
	std::clock_t t3 = std::clock();

	EXPECT_TRUE(mBST3.sameKeys(mBST3));
	std::clock_t t4 = std::clock();

	CheckRuntime(t1, t2, t3, t4, 10, 4);
}