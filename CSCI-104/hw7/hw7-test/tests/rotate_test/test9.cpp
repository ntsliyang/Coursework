#include "rotate_gtest_class.h"

TEST_F(RotateTest, Test9_SameKeysIdentical) 
{
	StressBST t1, t2;
	std::mt19937 g(942);
	InsSeq<StressKey, StressValue> ins;
	InsertRandom(t1, 10, g, ins);
	InsertInTree(t2, ins);
	EXPECT_EQ(true, t1.sameKeys(t2));
	EXPECT_EQ(true, t2.sameKeys(t1));
}