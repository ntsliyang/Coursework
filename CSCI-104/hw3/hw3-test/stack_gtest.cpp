/*
CS 104: Homework 2 Problem 5, Spring 2018
fullsort_gtest.cpp
*/

#include <algorithm> 
#include <fstream>
#include <string>
#include <vector>
#include "gtest/gtest.h"

#include "../stackstr.h"

#include <stack>

// const std::string kTestInputPrefix{ "fullsort_input/input" };
// const std::string kTestInputSuffix{ ".in" };

class StackStrTest : public testing::Test
{
public:
	void RunTest(int testNumber);

protected:
	StackStrTest() { }
	~StackStrTest() { }
	virtual void SetUp() { }
	virtual void TearDown() { }

	StackStr mStack;
};

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

/*
 * The the construction of LListStr
 */
TEST_F(StackStrTest, Test1)
{
	ASSERT_EQ(mStack.empty(), 1);
	ASSERT_EQ(mStack.size(), 0);
}

/*
 * The top of empty stack should return a empty string
 */ 
TEST_F(StackStrTest, Test2)
{
	EXPECT_EQ(mStack.top(), "");
}


/* 
 * push one element, the stack should function properly
 */ 
TEST_F(StackStrTest, Test3)
{
	mStack.push("Aaron");
	ASSERT_EQ(mStack.empty(), 0);
	ASSERT_EQ(mStack.size(), 1);
	EXPECT_EQ(mStack.top(), "Aaron");
}

/*  
 * push multiple element, the stack should function properly
 */ 
TEST_F(StackStrTest, Test4_Empty)
{
	for (int i = 0; i < 5; i++) {
		mStack.push(std::to_string(i));
		ASSERT_EQ(mStack.empty(), 0);
		ASSERT_EQ(mStack.size(), i+1);
		EXPECT_EQ(mStack.top(), std::to_string(i));
	}
}

TEST_F(StackStrTest, Test5)
{
	mStack.push("Aaron");
	mStack.pop();	
	ASSERT_EQ(mStack.empty(), 1);
	ASSERT_EQ(mStack.size(), 0);
	EXPECT_EQ(mStack.top(), "");
}

TEST_F(StackStrTest, Test6)
{
	for (int i = 0; i < 5; i++) {
		mStack.push(std::to_string(i));
	}
	for (int i = 4; i >= 0; i--) {
		ASSERT_EQ(mStack.empty(), 0 );
		ASSERT_EQ(mStack.size(), i+1 );
		EXPECT_EQ(mStack.top(), std::to_string(i));
		mStack.pop();
	}
	ASSERT_EQ(mStack.empty(), 1);
	ASSERT_EQ(mStack.size(), 0);
	EXPECT_EQ(mStack.top(), "");
}

TEST_F(StackStrTest, Test7)
{
	mStack.pop();
	mStack.pop();
	mStack.pop();
	ASSERT_EQ(mStack.empty(), 1);
	ASSERT_EQ(mStack.size(), 0);
	EXPECT_EQ(mStack.top(), "");
}

TEST_F(StackStrTest, Test8)
{
	mStack.pop();
	mStack.top();
	mStack.pop();
	mStack.top();
	for (int i = 0; i < 5; i++) {
		mStack.push(std::to_string(i));
		ASSERT_EQ(mStack.empty(), 0);
		ASSERT_EQ(mStack.size(), i+1);
		EXPECT_EQ(mStack.top(), std::to_string(i));
	}
	for (int i = 4; i >= 0; i--) {
		ASSERT_EQ(mStack.empty(), 0 );
		ASSERT_EQ(mStack.size(), i+1 );
		EXPECT_EQ(mStack.top(), std::to_string(i));
		mStack.pop();
	}
	ASSERT_EQ(mStack.empty(), 1);
	ASSERT_EQ(mStack.size(), 0);
	EXPECT_EQ(mStack.top(), "");
}

TEST_F(StackStrTest, Test9)
{
	std::stack<std::string> prophet; 
	std::ifstream input("p4/input1.txt");
	std::string str;
	while (input >> str) {
		if (str.length() % 3 == 0) {
			if (prophet.size() > 0){	
				mStack.pop();
				prophet.pop();
			}
		}
		else {
			mStack.push(str);
			prophet.push(str);
		}
		EXPECT_EQ(mStack.size(), prophet.size());
		EXPECT_EQ(mStack.empty(), prophet.empty());
		if (!prophet.empty()) {
			EXPECT_EQ(mStack.top(), prophet.top());
		}
	}

}

TEST_F(StackStrTest, Test10)
{
	std::stack<std::string> prophet; 
	std::ifstream input("p4/input.txt");
	std::string str;
	while (input >> str) {
		if (str.length() % 3 == 0) {
			if (prophet.size() > 0){	
				mStack.pop();
				prophet.pop();
			}
		}
		else {
			mStack.push(str);
			prophet.push(str);
		}
		EXPECT_EQ(mStack.size(), prophet.size());
		EXPECT_EQ(mStack.empty(), prophet.empty());
		if (!prophet.empty()) {
			EXPECT_EQ(mStack.top(), prophet.top());
		}
	}
}

TEST_F(StackStrTest, Test11) 
{
	for (int i = 0; i < 1000; i++) {
		mStack.push("a");
	}
	for (int i = 0; i < 1000; i++) {
		mStack.pop();
		mStack.top();
	}
}

TEST_F(StackStrTest, Test12) 
{
	for (int i = 0; i < 10000; i++) {
		mStack.push("a");
	}
	for (int i = 0; i < 10000; i++) {
		mStack.pop();
		mStack.top();
	}
}

TEST_F(StackStrTest, Test13) 
{
	for (int i = 0; i < 100000; i++) {
		mStack.push("a");
	}
	for (int i = 0; i < 100000; i++) {
		mStack.pop();
		mStack.top();
	}
}