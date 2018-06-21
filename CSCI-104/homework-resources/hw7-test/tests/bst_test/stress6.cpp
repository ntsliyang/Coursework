#include "bst_gtest_class.h"

TEST_F(BSTTest, Stress6_GetSmallest) 
{
	InsertFull(mBST1, 4);
	InsertFull(mBST2, 8);
	InsertFull(mBST3, 16);

	std::pair<StressKey, StressValue> exp{1, 0};

	std::clock_t t1 = std::clock();

	StressGetSmallest(mBST1);
	std::clock_t t2 = std::clock();

	StressGetSmallest(mBST2);
	std::clock_t t3 = std::clock();

	StressGetSmallest(mBST3);
	std::clock_t t4 = std::clock();

	std::clock_t times[] = {t1, t2, t3, t4};
	CheckRuntime(times, 5, 3);
}