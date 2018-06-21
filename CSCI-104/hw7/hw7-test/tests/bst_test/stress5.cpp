#include "bst_gtest_class.h"

TEST_F(BSTTest, Stress5_InternalFind) 
{
	InsertFull(mBST1, 4, mKey1);
	InsertFull(mBST2, 8, mKey1);
	InsertFull(mBST3, 16, mKey3);

	std::pair<StressKey, StressValue> exp{1, 0};

	std::clock_t t1 = std::clock();

	CheckInternalFind(mBST1, exp.first, &exp.second);
	std::clock_t t2 = std::clock();

	CheckInternalFind(mBST2, exp.first, &exp.second);
	std::clock_t t3 = std::clock();

	CheckInternalFind(mBST3, exp.first, &exp.second);
	std::clock_t t4 = std::clock();

	CheckRuntime(t1, t2, t3, t4, 5, 4);
}