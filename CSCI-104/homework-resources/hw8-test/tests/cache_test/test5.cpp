#include "cache_gtest_header.h"

TEST_F(CacheLRUTest, Test5_PutDuplicateKey) {
	TestCache cache(2);
	cache.put({1, 'a'});
	cache.put({2, 'b'});
	cache.put({1, 'c'}); // put a duplicate key
	EXPECT_NO_THROW(cache.get(1));
	EXPECT_NO_THROW(cache.get(2));
}