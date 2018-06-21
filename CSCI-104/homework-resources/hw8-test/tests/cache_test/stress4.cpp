#include "cache_gtest_header.h"

TEST_F(CacheLRUTest, Stress4_GetRecentPut) {
	std::mt19937 mtRand(500);

	std::clock_t t1 = std::clock();
	std::clock_t t2 = t1 + RandomPutGetRecent(10000, 100, mtRand);
	std::clock_t t3 = t2 + RandomPutGetRecent(10000, 1000, mtRand);
	std::clock_t t4 = t3 + RandomPutGetRecent(10000, 10000, mtRand);

	std::clock_t times[] = {t1, t2, t3, t4};
	CheckRuntime(times, 5, 15);
}
