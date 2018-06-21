#include "splay_gtest_header.h"

TEST_F(SplayTest, Stress2_Find) 
{
	std::mt19937 g(242);
	InsertRandom(mBST1, 1 << 4, g);
	InsertRandom(mBST2, 1 << 8, g);
	InsertRandom(mBST3, 1 << 16, g);

	std::clock_t t1 = std::clock();

	FindRandom(mBST1, mStressSize, g);
	std::clock_t t2 = std::clock();

	FindRandom(mBST2, mStressSize, g);
	std::clock_t t3 = std::clock();

	FindRandom(mBST3, mStressSize, g);
	std::clock_t t4 = std::clock();

	std::clock_t times[] = {t1, t2, t3, t4};
	CheckRuntime(times, 5, 4);
}