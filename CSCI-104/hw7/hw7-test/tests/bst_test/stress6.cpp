#include "bst_gtest_class.h"

TEST_F(BSTTest, Stress6_GetSmallest) 
{
	InsertFull(mBST1, 4, mKey1);
	InsertFull(mBST2, 8, mKey1);
	InsertFull(mBST3, 16, mKey3);

	std::pair<StressKey, StressValue> exp{1, 0};

	std::clock_t t1 = std::clock();

	CheckGetSmallest(mBST1, &exp);
	std::clock_t t2 = std::clock();

	CheckGetSmallest(mBST2, &exp);
	std::clock_t t3 = std::clock();

	CheckGetSmallest(mBST3, &exp);
	std::clock_t t4 = std::clock();

	CheckRuntime(t1, t2, t3, t4, 5, 4);
}