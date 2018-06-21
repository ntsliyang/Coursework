#include "cache_gtest_header.h"

TEST_F(CacheLRUTest, Test4_Put2Get2) {
	TestCache cache(2);
	cache.put({1, 'a'});
	cache.put({2, 'b'});
	ASSERT_NO_THROW(cache.get(1));
	EXPECT_EQ(1, cache.get(1).first);
	EXPECT_EQ('a', cache.get(1).second);
	ASSERT_NO_THROW(cache.get(2));
	EXPECT_EQ(2, cache.get(2).first);
	EXPECT_EQ('b', cache.get(2).second);
}