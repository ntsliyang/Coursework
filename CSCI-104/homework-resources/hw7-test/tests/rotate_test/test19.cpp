#include "rotate_gtest_class.h"

TEST_F(RotateTest, Test19_Transform100) 
{
	StressBST t1, t2, copy;
	std::mt19937 g(1942);
	InsSeq<StressKey, StressValue> ins;
	InsertRandom(t1, 100, g, ins);
	InsertInTree(copy, ins);
	std::shuffle(ins.begin(), ins.end(), g);
	InsertInTree(t2, ins);
	t1.transform(t2);
	CompareTreeStructure(copy.getRoot(), t1.getRoot());
	CompareTreeStructure(copy.getRoot(), t2.getRoot());
}