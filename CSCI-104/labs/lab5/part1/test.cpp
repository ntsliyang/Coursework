#include "fib.h"
#include "gtest/gtest.h"

TEST(FibTest, Nominal) {
	Fibonacci f;
	EXPECT_EQ(5, f.get(5));
	EXPECT_EQ(13, f.get(7));
}
