#include "rotate_gtest_class.h"

TEST_F(RotateTest, Test11_SameKeysDifferent) 
{
	StressBST t1, t2;
	std::mt19937 g(1142);
	InsSeq<StressKey, StressValue> ins;
	InsertRandom(t1, 10, g, ins);
	for (auto& kv : ins)
	{
		kv.first += 1;
	}
	std::shuffle(ins.begin(), ins.end(), g);
	InsertInTree(t2, ins);
	EXPECT_EQ(false, t1.sameKeys(t2));
	EXPECT_EQ(false, t2.sameKeys(t1));
}