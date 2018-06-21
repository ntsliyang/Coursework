#include "cache_gtest_header.h"

TEST_F(CacheLRUTest, Test6_RandomPutGet) {
	std::mt19937 mtRand(200);
	RandomPutGet(mStressSize, mtRand);
}