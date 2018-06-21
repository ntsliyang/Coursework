#include "bst_gtest_class.h"

TEST_F(BSTTest, Stress3_Insert) 
{
	std::clock_t t1 = std::clock();

	InsertFull(mBST1, 4, mKey1);
	std::clock_t t2 = std::clock();

	InsertFull(mBST2, 8, mKey1);
	std::clock_t t3 = std::clock();

	InsertFull(mBST3, 16, mKey3);
	std::clock_t t4 = std::clock();

	CheckRuntime(t1, t2, t3, t4, 50, 4);
}