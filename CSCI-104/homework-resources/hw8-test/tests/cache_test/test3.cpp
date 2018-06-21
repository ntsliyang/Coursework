#include "cache_gtest_header.h"

TEST_F(CacheLRUTest, Test3_CacheMissCapacity1) {
	cacheLRU<int, int> cache(1);
	cache.put({1, 2});
	ASSERT_NO_THROW(cache.get(1));
	EXPECT_EQ(1, cache.get(1).first);
	EXPECT_EQ(2, cache.get(1).second);
	cache.put({5, 7});
	EXPECT_THROW(cache.get(1), std::logic_error);
	ASSERT_NO_THROW(cache.get(5));
	EXPECT_EQ(5, cache.get(5).first);
	EXPECT_EQ(7, cache.get(5).second);
}