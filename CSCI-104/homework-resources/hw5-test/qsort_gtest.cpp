/*
CS 104: Homework 5 Problem 1, Spring 2018
functor_gtest.cpp
*/

#include <algorithm> 
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "gtest/gtest.h"

#include "../qsort.h"

struct IntLessThan {
    bool operator()(const int& lhs, const int& rhs) {
        return lhs < rhs;
    }
} ilt;

struct IntGreaterThan {
    bool operator()(const int& lhs, const int& rhs) {
        return lhs > rhs;
    }
} igt;

struct StrLessThan {
    bool operator()(const std::string& lhs, const std::string& rhs) {
        return lhs < rhs;
    }
} slt;

struct StrGreaterThan {
    bool operator()(const std::string& lhs, const std::string& rhs) {
        return lhs > rhs;
    }
} sgt;

struct StrLengthLessThan {
    bool operator()(const std::string& lhs, const std::string& rhs) {
        return lhs.length() < rhs.length();
    }
} sllt;

class QSortTest : public testing::Test
{
public:
	void RunTest(int testNumber);

protected:
	QSortTest() { }
	~QSortTest() { }
};

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

/*
 * Testing with int less than operator samll
 * */
TEST_F(QSortTest, Test1)
{
    std::vector<int> v;
    std::vector<int> ve;
    for (int i = 0; i < 3; i++) {
        v.push_back(i);
    }
    std::mt19937 g(3);
    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::back_inserter(ve));
    QuickSort(v, igt);
    std::sort(ve.begin(), ve.end(), igt);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(v[i], ve[i]);
    }

    EXPECT_EQ(v.size(), ve.size());
}

/*
 * Testing with int greater than operator small
 */ 
TEST_F(QSortTest, Test2)
{
    std::vector<int> v;
    std::vector<int> ve;
    for (int i = 0; i < 5; i++) {
        v.push_back(i);
    }
    std::mt19937 g(3);
    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::back_inserter(ve));
    QuickSort(v, igt);
    std::sort(ve.begin(), ve.end(), igt);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(v[i], ve[i]);
    }

    EXPECT_EQ(v.size(), ve.size());
}

/* 
 * String Less than operator small
 */ 
TEST_F(QSortTest, Test3)
{
    std::vector<std::string> v;
    std::vector<std::string> ve;
    for (int i = 0; i < 10; i++) {
        v.push_back(std::to_string(i));
    }
    std::mt19937 g(3);
    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::back_inserter(ve));
    QuickSort(v, slt);
    std::sort(ve.begin(), ve.end(), slt);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v[i], ve[i]);
    }

    EXPECT_EQ(v.size(), ve.size());
}

/*  
 * String Greater than opeartor small
 */ 
TEST_F(QSortTest, Test4)
{
    std::vector<std::string> v;
    std::vector<std::string> ve;
    for (int i = 0; i < 10; i++) {
        v.push_back(std::to_string(i));
    }
    std::mt19937 g(3);
    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::back_inserter(ve));
    QuickSort(v, sgt);
    std::sort(ve.begin(), ve.end(), sgt);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v[i], ve[i]);
    }

    EXPECT_EQ(v.size(), ve.size());
}

/*
 * Test Empty
 */
TEST_F(QSortTest, Test5)
{
    std::vector<std::string> v;
    QuickSort(v, sgt);
    EXPECT_EQ(v.size(), 0);
}

/*
 * Test with string length comparator
 */
TEST_F(QSortTest, Test6)
{
    std::vector<std::string> v;
    std::vector<std::string> ve;
    std::string s;
    for (int i = 0; i < 10; i++) {
        s += std::to_string(i);
        v.push_back(s);
    }
    std::mt19937 g(3);
    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::back_inserter(ve));
    QuickSort(v, sllt);
    std::sort(ve.begin(), ve.end(), sllt);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v[i], ve[i]);
    }

    EXPECT_EQ(v.size(), ve.size());
}

/*
 * Test with random generated int
 */
TEST_F(QSortTest, Test7)
{
    std::vector<int> v;
    std::vector<int> ve;
    std::mt19937 g(3);
    for (int i = 0; i < 10; i++) {
        v.push_back(fmod(g(), 100.0f));
    }

    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::back_inserter(ve));
    QuickSort(v, ilt);
    std::sort(ve.begin(), ve.end(), ilt);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(v[i], ve[i]);
    }

    EXPECT_EQ(v.size(), ve.size());
}

/*
 * Random Int Test with duplicated numbers
 */
TEST_F(QSortTest, Test8)
{
    std::vector<int> v;
    std::vector<int> ve;
    std::mt19937 g(3);
    for (int i = 0; i < 100; i++) {
        v.push_back(fmod(g(), 10.0f));
    }

    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::back_inserter(ve));
    QuickSort(v, ilt);
    std::sort(ve.begin(), ve.end(), ilt);

    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(v[i], ve[i]);
    }

    EXPECT_EQ(v.size(), ve.size());
}


/*
 * Random Int Test with all duplicated numbers
 */
TEST_F(QSortTest, Test9)
{
    std::vector<int> v;
    std::vector<int> ve;
    std::mt19937 g(3);
    for (int i = 0; i < 99; i++) {
        v.push_back(1);
    }

    v.push_back(2);

    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::back_inserter(ve));
    QuickSort(v, ilt);
    std::sort(ve.begin(), ve.end(), ilt);

    EXPECT_EQ(v.size(), ve.size());
    
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(v[i], ve[i]);
    }
}

/*
 * Random Int Large Test Case
 */
TEST_F(QSortTest, Test10)
{
    std::vector<int> v;
    std::vector<int> ve;
    std::mt19937 g(3);
    for (int i = 0; i < 1000; i++) {
        v.push_back(fmod(g(), 1000.0f));
    }

    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::back_inserter(ve));
    QuickSort(v, ilt);
    std::sort(ve.begin(), ve.end(), ilt);

    EXPECT_EQ(v.size(), ve.size());
    
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(v[i], ve[i]);
    }
}

TEST_F(QSortTest, Test11)
{
    std::vector<int> v;
    std::mt19937 g(3);
    for (int i = 0; i < 1000; i++) {
        v.push_back(i);
    }
    std::shuffle(v.begin(), v.end(), g);

    QuickSort(v, igt);    
}


TEST_F(QSortTest, Test12)
{
    std::vector<int> v;
    std::mt19937 g(3);
    for (int i = 0; i < 10000; i++) {
        v.push_back(i);
    }
    std::shuffle(v.begin(), v.end(), g);
	
    QuickSort(v, igt);    
}

TEST_F(QSortTest, Test13)
{
    std::vector<int> v;
    std::mt19937 g(3);
    for (int i = 0; i < 100000; i++) {
        v.push_back(i);
    }
    std::shuffle(v.begin(), v.end(), g);

    QuickSort(v, igt);    
}
