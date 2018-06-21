/*
	CS 104: Homework 2 Problem 7 
	gtest_LListStr.cpp
	Contains unit tests for checking student's implementations of a 
	doubly linked list that tracks integers. 
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "../lliststr.h"

class LListStrTest : public testing::Test
{
	protected:
		LListStrTest() 
		{ 

		}

		~LListStrTest() 
		{ 

		}

		virtual void SetUp() 
		{
			mLListStr = new LListStr();
			srand(10442);
		}

		virtual void TearDown() 
		{ 
			delete mLListStr;
		}

		LListStr *mLListStr;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(LListStrTest, Test1_InitiallyEmpty)
{
	EXPECT_TRUE(mLListStr->empty());
}

TEST_F(LListStrTest, Test2_InitiallySizeZero)
{
	EXPECT_EQ(mLListStr->size(), 0);
}

TEST_F(LListStrTest, Test3_EmptyInsertLess)
{
	mLListStr->insert(-1, "a");
	EXPECT_TRUE(mLListStr->empty());
	EXPECT_EQ(mLListStr->size(), 0);
}

TEST_F(LListStrTest, Test4_EmptyInsertGreater)
{
	mLListStr->insert(1, "10");
	EXPECT_TRUE(mLListStr->empty());
	EXPECT_EQ(mLListStr->size(), 0);
}

TEST_F(LListStrTest, Test5_EmptyGetLess)
{
	EXPECT_EQ(mLListStr->get(-1), "");
}

TEST_F(LListStrTest, Test6_EmptyGetGreater)
{
	EXPECT_EQ(mLListStr->get(1), "");	
}

TEST_F(LListStrTest, Test7_EmptyRemoveLess)
{
	mLListStr->remove(-1);
	EXPECT_TRUE(mLListStr->empty());
	EXPECT_EQ(mLListStr->size(), 0);
}

TEST_F(LListStrTest, Test8_EmptyRemoveGreater)
{
	mLListStr->remove(1);
	EXPECT_TRUE(mLListStr->empty());
	EXPECT_EQ(mLListStr->size(), 0);
}

TEST_F(LListStrTest, Test9_SingleInsertNotEmpty)
{
	mLListStr->insert(0, "10");
	EXPECT_FALSE(mLListStr->empty());
}

TEST_F(LListStrTest, Test10_SingleInsertSize)
{
	mLListStr->insert(0, "10");
	EXPECT_EQ(mLListStr->size(), 1);
}

TEST_F(LListStrTest, Test11_SingleInsertThenRemoveEmpty)
{
	mLListStr->insert(0, "10");
	mLListStr->remove(0);
	EXPECT_TRUE(mLListStr->empty());
}

TEST_F(LListStrTest, Test12_SingleInsertThenRemoveSize)
{
	mLListStr->insert(0, "10");
	mLListStr->remove(0);
	EXPECT_EQ(mLListStr->size(), 0);
}

TEST_F(LListStrTest, Test13_MultipleInsertHeadCheckOrder)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->insert(0, std::to_string(i));
		EXPECT_EQ(mLListStr->size(), i + 1);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListStr->get(i), std::to_string(NUMBER_OF_ELEMENTS - i - 1));
	}
}

TEST_F(LListStrTest, Test14_MultipleInsertTailCheckOrder)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->insert(mLListStr->size(), std::to_string(i));
		EXPECT_EQ(mLListStr->size(), i + 1);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListStr->get(i), std::to_string(i));
	}
}

TEST_F(LListStrTest, Test15_MultipleInsertMiddleCheckOrder)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->insert(mLListStr->size() / 2, std::to_string(i));
		EXPECT_EQ(mLListStr->size(), i + 1);
	}

	EXPECT_EQ(mLListStr->get(0), "1");
	EXPECT_EQ(mLListStr->get(1), "3");
	EXPECT_EQ(mLListStr->get(2), "5");
	EXPECT_EQ(mLListStr->get(3), "7");
	EXPECT_EQ(mLListStr->get(4), "9");
	EXPECT_EQ(mLListStr->get(5), "8");
	EXPECT_EQ(mLListStr->get(6), "6");
	EXPECT_EQ(mLListStr->get(7), "4");
	EXPECT_EQ(mLListStr->get(8), "2");
	EXPECT_EQ(mLListStr->get(9), "0");
}

TEST_F(LListStrTest, Test16_MultipleInsertRandomThenRemoveRandom)
{
	const int NUMBER_OF_ELEMENTS = 10;
	std::vector<std::string> actual;


	mLListStr->insert(0, "0");
	actual.insert(actual.begin(), "0");

	for(int i = 1; i < NUMBER_OF_ELEMENTS; ++i)
	{
		int index = rand() % mLListStr->size();
		mLListStr->insert(index, std::to_string(i));
		actual.insert(actual.begin() + index, std::to_string(i));
		EXPECT_EQ(mLListStr->size(), i + 1);
	}

	for(unsigned int i = 0; i < actual.size(); ++i)
	{
		EXPECT_EQ(mLListStr->get(i), actual[i]);
	}

	int size = mLListStr->size();
	while(mLListStr->size() != 1)
	{
		mLListStr->remove(rand() % (mLListStr->size() - 1));
		EXPECT_EQ(mLListStr->size(), --size);
	}
}

TEST_F(LListStrTest, Test17_EmptySetLess)
{
	mLListStr->set(-1, "a");
	EXPECT_EQ(mLListStr->size(), 0);
	EXPECT_TRUE(mLListStr->empty());
}

TEST_F(LListStrTest, Test18_EmptySetGreater)
{
	mLListStr->set(1, "a");
	EXPECT_EQ(mLListStr->size(), 0);
	EXPECT_TRUE(mLListStr->empty());
}

TEST_F(LListStrTest, Test19_SingleSet)
{
	mLListStr->insert(0, "10");
	mLListStr->set(0, "1");
	EXPECT_EQ(mLListStr->size(), 1);
	EXPECT_FALSE(mLListStr->empty());
	EXPECT_EQ(mLListStr->get(0), "1");
}

TEST_F(LListStrTest, Test20_SingleSetRemove)
{
	mLListStr->insert(0, "10");
	mLListStr->set(0, "1");
	mLListStr->remove(0);
	EXPECT_EQ(mLListStr->size(), 0);
	EXPECT_TRUE(mLListStr->empty());
}

TEST_F(LListStrTest, Test21_MultipleSetHeadCheckOrder)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->insert(0, std::to_string(i));
		EXPECT_EQ(mLListStr->size(), i + 1);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->set(0, std::to_string(NUMBER_OF_ELEMENTS - 1 - i));
		EXPECT_EQ(mLListStr->get(0), std::to_string(NUMBER_OF_ELEMENTS - 1 - i));
		mLListStr->remove(0);
	}
}

TEST_F(LListStrTest, Test22_MultipleSetTailCheckOrder)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->insert(0, std::to_string(i));
		EXPECT_EQ(mLListStr->size(), i + 1);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->set(NUMBER_OF_ELEMENTS - 1 - i, std::to_string(i));
		EXPECT_EQ(mLListStr->get(NUMBER_OF_ELEMENTS - 1 - i), std::to_string(i));
		mLListStr->remove(NUMBER_OF_ELEMENTS - 1 - i);
	}
}

TEST_F(LListStrTest, Test23_MultipleSetMiddleCheckOrder)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->insert(i, std::to_string(i));
		EXPECT_EQ(mLListStr->size(), i + 1);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		if(i % 2 == 0)
		{
			mLListStr->set(i, "a");
			EXPECT_EQ(mLListStr->get(i), "a");
		}
		else
		{
			EXPECT_EQ(mLListStr->get(i), std::to_string(i));
		}
	}
}


TEST_F(LListStrTest, Test24_InsertRemoveInsert)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->insert(0, std::to_string(i));
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->remove(0);
	}

	std::vector<std::string> actual;

	for(int i = 10; i < NUMBER_OF_ELEMENTS + 10; ++i)
	{
		mLListStr->insert(0, std::to_string(i));
		actual.insert(actual.begin(), std::to_string(i));
	}

	for(unsigned int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListStr->get(i), actual[i]);
	}
	EXPECT_EQ(mLListStr->size(), actual.size());
	EXPECT_EQ(mLListStr->empty(), actual.empty());
}

TEST_F(LListStrTest, Test25_LargeInputStressTest)
{
	const int NUMBER_OF_ELEMENTS = 10000;

	std::vector<std::string> actual;
	mLListStr->insert(0, "42");
	actual.insert(actual.begin(), "42");

	for(int i = 1; i < NUMBER_OF_ELEMENTS; ++i)
	{
		int index = rand() % actual.size();
		mLListStr->insert(index, std::to_string(i));
		actual.insert(actual.begin() + index, std::to_string(i));
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		int index = rand() % actual.size();
		mLListStr->set(index, std::to_string(i));
		actual[index] = std::to_string(i);
	}

	for(unsigned int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListStr->get(i), actual[i]);
	}
	EXPECT_EQ(mLListStr->size(), actual.size());
	EXPECT_EQ(mLListStr->empty(), actual.empty());

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListStr->remove(0);
		actual.erase(actual.begin());
	}

	mLListStr->insert(0, "42");
	actual.insert(actual.begin(), "42");

	for(int i = 1; i < NUMBER_OF_ELEMENTS; ++i)
	{
		int index = rand() % actual.size();
		mLListStr->insert(index, std::to_string(i));
		actual.insert(actual.begin() + index, std::to_string(i));
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		int index = rand() % actual.size();
		mLListStr->set(index, std::to_string(i));
		actual[index] = std::to_string(i);
	}

	for(unsigned int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListStr->get(i), actual[i]);
	}
	EXPECT_EQ(mLListStr->size(), actual.size());
	EXPECT_EQ(mLListStr->empty(), actual.empty());
}
