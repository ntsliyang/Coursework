#include "bst_gtest_class.h"

TEST_F(BSTTest, Stress1_Height) 
{
	InsertFull(mBST1, 14);
	InsertFull(mBST2, 15);
	InsertFull(mBST3, 16);

	std::clock_t t1 = std::clock();

	StressHeight(mBST1);
	std::clock_t t2 = std::clock();

	StressHeight(mBST2);
	std::clock_t t3 = std::clock();

	StressHeight(mBST3);
	std::clock_t t4 = std::clock();

	std::clock_t times[] = {t1, t2, t3, t4};
	CheckRuntime(times, 5, 1.2);
}