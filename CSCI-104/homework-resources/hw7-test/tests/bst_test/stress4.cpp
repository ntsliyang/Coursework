#include "bst_gtest_class.h"

TEST_F(BSTTest, Stress4_Remove) 
{
	InsertFull(mBST1, 4);
	InsertFull(mBST2, 8);
	InsertFull(mBST3, 16);

	std::clock_t t1 = std::clock();

	StressRemove(mBST1);
	std::clock_t t2 = std::clock();

	StressRemove(mBST2);
	std::clock_t t3 = std::clock();

	StressRemove(mBST3);
	std::clock_t t4 = std::clock();

	std::clock_t times[] = {t1, t2, t3, t4};
	CheckRuntime(times, 5, 3);
}