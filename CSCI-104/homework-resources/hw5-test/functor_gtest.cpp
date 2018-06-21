/*
CS 104: Homework 5 Problem 1, Spring 2018
functor_gtest.cpp
*/

#include <algorithm> 
#include <fstream>
#include <string>
#include <vector>
#include "gtest/gtest.h"

// #include "../functor.h"
#include "../functor.cpp"

class FunctorTest : public testing::Test
{
public:
	void RunTest(int testNumber);

protected:
	FunctorTest() { }
	~FunctorTest() { }
	NumStrComp comp;
};

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

/*
 * Basic Testing with string comparion
 * */
TEST_F(FunctorTest, Test1)
{
    EXPECT_EQ(comp("AAA", "BBB"), 1);
    EXPECT_EQ(comp("BBB", "AAA"), 0);
    
}

/*
 * 000000000 < A
 */ 
TEST_F(FunctorTest, Test2)
{
    EXPECT_EQ(comp("A", "00000000"), 0);
    EXPECT_EQ(comp("00000000", "A"), 1);
}

/* 
 * Tie Breaking by lexicographical order
 */ 
TEST_F(FunctorTest, Test3)
{
    EXPECT_EQ(comp("ACE", "BCD"), 1);
    EXPECT_EQ(comp("BCD", "ACE"), 0);
}

/*  
 * lower case should have same value
 */ 
TEST_F(FunctorTest, Test4)
{
    EXPECT_EQ(comp("aaa", "BBB"), 1);
    EXPECT_EQ(comp("BBB", "aaa"), 0);
    EXPECT_EQ(comp("aAa", "bBB"), 1);
    EXPECT_EQ(comp("bBb", "AaA"), 0);
    EXPECT_EQ(comp("ace", "BCD"), 0);
    EXPECT_EQ(comp("bcd", "ACE"), 0);
}

/*
 * Mixture of number and values
 */
TEST_F(FunctorTest, Test5)
{
    //26, 25
    EXPECT_EQ(comp("B4A1", "C94"), 0);
    EXPECT_EQ(comp("C94", "b4a4"), 1);
}