#include "rotate_gtest_class.h"

TEST_F(RotateTest, Test12_SameKeysDifferentLength) 
{
	StressBST t1, t2;
	std::mt19937 g(1242);
	InsSeq<StressKey, StressValue> ins;
	InsertRandom(t1, 10, g, ins);
	std::shuffle(ins.begin(), ins.end(), g);
	InsSeq<StressKey, StressValue> trunc(ins.begin(), ins.begin() + ins.size()/2);
	InsertInTree(t2, trunc);
	EXPECT_EQ(false, t1.sameKeys(t2));
	EXPECT_EQ(false, t2.sameKeys(t1));
}