#include "cache_gtest_header.h"

TEST_F(CacheLRUTest, Stress3_GetRecentGet) {
	TestCache cache(10000);
	InOrderPutToCache(cache, 10000);
	ASSERT_NO_THROW(cache.get(0)); // to avoid t2-t1 being larger than expected

	std::clock_t t1 = std::clock();

	InOrderGetRecentFromCache(cache, 0, 1000);
	std::clock_t t2 = std::clock();

	InOrderGetRecentFromCache(cache, 0, 10000);
	std::clock_t t3 = std::clock();

	InOrderGetRecentFromCache(cache, 0, 100000);
	std::clock_t t4 = std::clock();

	std::clock_t times[] = {t1, t2, t3, t4};
	CheckRuntime(times, 5, 15);
}