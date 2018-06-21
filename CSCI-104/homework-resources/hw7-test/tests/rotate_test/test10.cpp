#include "rotate_gtest_class.h"

TEST_F(RotateTest, Test10_SameKeysIsomorphic) 
{
	StressBST t1, t2;
	std::mt19937 g(1042);
	InsSeq<StressKey, StressValue> ins;
	InsertRandom(t1, 10, g, ins);
	std::shuffle(ins.begin(), ins.end(), g);
	InsertInTree(t2, ins);
	EXPECT_EQ(true, t1.sameKeys(t2));
	EXPECT_EQ(true, t2.sameKeys(t1));
}