#include "bst_gtest_class.h"

TEST_F(BSTTest, Stress4_Remove) 
{
	InsertFull(mBST1, 4, mKey1);
	InsertFull(mBST2, 8, mKey1);
	InsertFull(mBST3, 16, mKey3);

	std::mt19937 g(42);
	std::shuffle(mKey1.begin(), mKey1.end(), g);
	std::shuffle(mKey2.begin(), mKey2.end(), g);
	std::shuffle(mKey3.begin(), mKey3.end(), g);

	std::clock_t t1 = std::clock();

	RemoveFromTree(mBST1, mKey1);
	std::clock_t t2 = std::clock();

	RemoveFromTree(mBST2, mKey2);
	std::clock_t t3 = std::clock();

	RemoveFromTree(mBST3, mKey3);
	std::clock_t t4 = std::clock();

	CheckRuntime(t1, t2, t3, t4, 50, 4);
}