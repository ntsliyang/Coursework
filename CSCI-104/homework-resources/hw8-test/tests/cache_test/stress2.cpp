#include "cache_gtest_header.h"

TEST_F(CacheLRUTest, Stress2_RandomGetRuntime) {
	std::mt19937 mtRand(400);
	TestCache cache1(1 << 17); // 2^4
	TestCache cache2(1 << 17); // 2^8
	TestCache cache3(1 << 17); // 2^16
	RandomPutToCache(cache1, 1 << 4, mtRand);
	RandomPutToCache(cache2, 1 << 8, mtRand);
	RandomPutToCache(cache3, 1 << 16, mtRand);

	std::clock_t t1 = std::clock();

	RandomGetFromCache(cache1, mStressSize, mtRand);
	std::clock_t t2 = std::clock();

	RandomGetFromCache(cache2, mStressSize, mtRand);
	std::clock_t t3 = std::clock();

	RandomGetFromCache(cache3, mStressSize, mtRand);
	std::clock_t t4 = std::clock();

	std::clock_t times[] = {t1, t2, t3, t4};
	CheckRuntime(times, 5, 4);
}