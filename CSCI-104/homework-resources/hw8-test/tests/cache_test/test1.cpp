#include "cache_gtest_header.h"

TEST_F(CacheLRUTest, Test1_EmptyCache) {
	cacheLRU<int, int> cache(1);
	EXPECT_THROW(cache.get(1), std::logic_error);
}