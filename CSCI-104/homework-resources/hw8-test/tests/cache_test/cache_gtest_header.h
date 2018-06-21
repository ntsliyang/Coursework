#include "../../../cacheLRU.h"
#include "gtest/gtest.h"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using TestKey = int;
using TestValue = char;
using TestCache = cacheLRU<TestKey, TestValue>;

class CacheLRUTest : public testing::Test {
protected:
	void CheckRuntime(std::clock_t times[4], double ignoreLessThan, double scalingFactor);
	void RandomPutToCache(TestCache& cache, int numPuts, std::mt19937& mtRand);
	void RandomGetFromCache(TestCache& cache, int numGets, std::mt19937& mtRand);
	void InOrderPutToCache(TestCache& cache, int numPuts);
	void InOrderGetFromCache(TestCache& cache, int numGets);
	void InOrderGetRecentFromCache(TestCache& cache, TestKey getKey, int numRecents);
	void RandomPutGet(int capacity, std::mt19937& mtRand);
	std::clock_t RandomPutGetRecent(int capacity, int numOperations, std::mt19937& mtRand);
protected:
	int mStressSize = 1000;
};

void CacheLRUTest::CheckRuntime(std::clock_t times[4], double ignoreLessThan, double scalingFactor) {
	double elapsed1 = double(times[1] - times[0]) / CLOCKS_PER_SEC * 1000;
  	double elapsed2 = double(times[2] - times[1]) / CLOCKS_PER_SEC * 1000;
  	double elapsed3 = double(times[3] - times[2]) / CLOCKS_PER_SEC * 1000;

  	std::cout << "cache1: " << elapsed1 << std::endl;
  	std::cout << "cache2: " << elapsed2 << std::endl;
  	std::cout << "cache3: " << elapsed3 << std::endl;

  	double scale1 = elapsed2 / elapsed1;
  	double scale2 = elapsed3 / elapsed2;
  	EXPECT_TRUE(elapsed1 < ignoreLessThan || scale1 < scalingFactor);
  	EXPECT_TRUE(elapsed2 < ignoreLessThan || scale2 < scalingFactor);
}

void CacheLRUTest::RandomPutToCache(TestCache& cache, int numPuts, std::mt19937& mtRand) {
	for(int i = 0; i < numPuts; ++i) {
		cache.put({static_cast<TestKey>(mtRand()), 'a'});
	}
}

void CacheLRUTest::RandomGetFromCache(TestCache& cache, int numGets, std::mt19937& mtRand) {
	for(int i = 0; i < numGets; ++i) {
		try {
			cache.get(static_cast<TestKey>(mtRand()));
		} catch (const std::exception&) {
		}
	}
}

void CacheLRUTest::InOrderPutToCache(TestCache& cache, int numPuts) {
	for(int i = 0; i < numPuts; ++i) {
		cache.put({i, 'a'});
	}
}

void CacheLRUTest::InOrderGetFromCache(TestCache& cache, int numGets) {
	for(int i = 0; i < numGets; ++i) {
		EXPECT_NO_THROW(cache.get(i));
	}
}

void CacheLRUTest::InOrderGetRecentFromCache(TestCache& cache, TestKey getKey, int numRecents) {
	for(int i = 0; i < numRecents; ++i) {
		EXPECT_NO_THROW(cache.get(getKey));
	}
}

void CacheLRUTest::RandomPutGet(int capacity, std::mt19937& mtRand) {
	TestCache cache(capacity);
	std::vector<TestKey> allKeys(capacity);
	for(int i = 0; i < capacity; ++i) {
		TestKey key = static_cast<TestKey>(mtRand());
		cache.put({key,'a'});
		allKeys[i] = key;
	}
	
	std::shuffle(allKeys.begin(), allKeys.end(), mtRand);
	for(const auto& i : allKeys) {
		ASSERT_NO_THROW(cache.get(i));
		EXPECT_EQ(i, cache.get(i).first);
		EXPECT_EQ('a', cache.get(i).second);
	}
}

std::clock_t CacheLRUTest::RandomPutGetRecent(int capacity, int numOperations, std::mt19937& mtRand) {
	std::clock_t init = std::clock();
	std::clock_t start, end;
	std::clock_t final = init;
	TestCache cache(capacity);
	for(int i = 0; i < numOperations; ++i) {
		TestKey key = static_cast<TestKey>(mtRand());
		cache.put({key,'a'});

		start = std::clock();
		try{
			EXPECT_EQ('a', cache.get(key).second);
		} catch (const std::exception&) {
			EXPECT_TRUE(false);
		}
		end = std::clock();
		final += end - start;
	}
	return final - init;
}