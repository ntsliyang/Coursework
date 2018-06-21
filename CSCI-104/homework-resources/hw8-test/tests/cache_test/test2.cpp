#include "cache_gtest_header.h"

TEST_F(CacheLRUTest, Test2_SimplePut1Get1) {
	cacheLRU<int, int> cache(1);
	cache.put({1, 5});
	ASSERT_NO_THROW(cache.get(1));
	EXPECT_EQ(1, cache.get(1).first);
	EXPECT_EQ(5, cache.get(1).second);
}