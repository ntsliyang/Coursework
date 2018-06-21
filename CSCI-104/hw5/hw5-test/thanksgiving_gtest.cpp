#include <algorithm> 
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "gtest/gtest.h"

#include "../Thanksgiving.cpp"

#define TEST_PLATES(turkey, potato, turkeySet, potatoSet, value)  \
std::set<int> studentTurkeySet;\
std::set<int> studentPotatoSet;\
std::vector<std::pair<int, int> > plates = assignPlates(turkey, potatos); \
ASSERT_EQ(plates.size(), turkey.size());\
for (auto& i: plates) { \
    EXPECT_EQ(i.first + i.second, value);\
    studentTurkeySet.insert(i.first);\
    studentPotatoSet.insert(i.second);\
}\
auto i = turkeySet.begin();\
auto j = potatoSet.begin();\
auto k = studentTurkeySet.begin();\
auto l = studentPotatoSet.begin();\
ASSERT_EQ(turkeySet.size(), studentTurkeySet.size());\
ASSERT_EQ(potatoSet.size(), studentPotatoSet.size());\
while (i!=turkeySet.end()) {\
    EXPECT_EQ(*i, *k);\
    EXPECT_EQ(*j, *l);\
    i++; j++; k++; l++;\
}\

class ThanksgivingTest : public testing::Test
{
public:
	void RunTest(int testNumber);

protected:
	ThanksgivingTest() { }
	~ThanksgivingTest() { }
};

/*
 * Simple test size 1
 * */
TEST_F(ThanksgivingTest, Test1)
{
    std::vector<int> turkey({1});
    std::vector<int> potatos({2});
    std::vector<std::pair<int, int> > plates = assignPlates(turkey, potatos);
    
    EXPECT_EQ(plates.size(), 1);
    EXPECT_EQ(plates[0].first, 1);
    EXPECT_EQ(plates[0].second, 2);
}

/*
 * Simple test size 2
 * */
TEST_F(ThanksgivingTest, Test2)
{
    std::vector<int> turkey({1, 2});
    std::vector<int> potatos({2, 1});
    std::set<int> turkeySet({1, 2});
    std::set<int> potatoSet({1, 2});
    TEST_PLATES(turkey, potatos, turkeySet, potatoSet, 3);
}

/*
 * Unordered test size 2
 */
TEST_F(ThanksgivingTest, Test3)
{
    std::vector<int> turkey({1, 2});
    std::vector<int> potatos({3, 4});
    std::set<int> turkeySet({1, 2});
    std::set<int> potatoSet({3, 4});
    TEST_PLATES(turkey, potatos, turkeySet, potatoSet, 5);
}

/*
 * Impossible test size 2
 */
TEST_F(ThanksgivingTest, Test4)
{
    std::vector<int> turkey({1, 2});
    std::vector<int> potatos({4, 6});
    std::vector<std::pair<int, int> > plates = assignPlates(turkey, potatos); 
    EXPECT_EQ(plates.size(), 0);
}

/*
 * EXPECT THROW
 */
TEST_F(ThanksgivingTest, Test5)
{
    std::vector<int> turkey({1, 2, 5});
    std::vector<int> potatos({4, 6});
    EXPECT_THROW(assignPlates(turkey, potatos)
    , LengthMismatch);
}

/*
 * EXPECT THROW correct error message
 */
TEST_F(ThanksgivingTest, Test6)
{
    std::vector<int> turkey({1, 2, 5});
    std::vector<int> potatos({4, 6});

    EXPECT_THROW(assignPlates(turkey, potatos)
    , LengthMismatch);

    try {
        assignPlates(turkey, potatos);
    } catch (LengthMismatch& lme) {
        std::string msg = lme.what();
        EXPECT_EQ(msg, "Input data structures have lengths 3 and 2");
    }

}


/*
 * Sample Case
 */
TEST_F(ThanksgivingTest, Test7)
{
    std::vector<int> turkey({500, 550, 580});
    std::vector<int> potatos({440, 470, 520});
    std::set<int> turkeySet({500, 550, 580});
    std::set<int> potatoSet({440, 470, 520});
    TEST_PLATES(turkey, potatos, turkeySet, potatoSet, 1020);
}

/*
 * Unordered test size 10
 */
TEST_F(ThanksgivingTest, Test8)
{
    std::vector<int> turkey({3, 5, 1, 2, 8, 4, 6, 9, 10, 7});
    std::vector<int> potatos({15, 13, 11, 20, 14, 18, 16, 17, 19, 12});
    std::set<int> turkeySet({3, 5, 1, 2, 8, 4, 6, 9, 10, 7});
    std::set<int> potatoSet({15, 13, 11, 20, 14, 18, 16, 17, 19, 12});
    TEST_PLATES(turkey, potatos, turkeySet, potatoSet, 21);
}

/*
 * Random Test 500
 */
TEST_F(ThanksgivingTest, Test9)
{
    std::vector<int> turkey;
    std::vector<int> potatos;
    std::set<int> turkeySet;
    std::set<int> potatoSet;
    srand(328);
    std::mt19937 g(3);
    for (int i = 0; i < 500; i++) {
        int sample = rand() % 20000;
        if (turkeySet.find(sample) == turkeySet.end()) {
            turkeySet.insert(sample);
            potatoSet.insert(20000 - sample);
            turkey.push_back(sample);
            potatos.push_back(20000 - sample);
        }
    }
    std::shuffle(turkey.begin(), turkey.end(), g);
    std::shuffle(potatos.begin(), potatos.end(), g);
    
    TEST_PLATES(turkey, potatos, turkeySet, potatoSet, 20000);
}

/*
 * Random Test 5000
 */
TEST_F(ThanksgivingTest, Test10)
{
    std::vector<int> turkey;
    std::vector<int> potatos;
    std::set<int> turkeySet;
    std::set<int> potatoSet;
    srand(328);
    std::mt19937 g(3);
    for (int i = 0; i < 5000; i++) {
        int sample = rand() % 200000;
        if (turkeySet.find(sample) == turkeySet.end()) {
            turkeySet.insert(sample);
            potatoSet.insert(200000 - sample);
            turkey.push_back(sample);
            potatos.push_back(200000 - sample);
        }
    }
    std::shuffle(turkey.begin(), turkey.end(), g);
    std::shuffle(potatos.begin(), potatos.end(), g);
    
    TEST_PLATES(turkey, potatos, turkeySet, potatoSet, 200000);
}

/*
 * Random Test 50000
 */
TEST_F(ThanksgivingTest, Test11)
{
    std::vector<int> turkey;
    std::vector<int> potatos;
    std::set<int> turkeySet;
    std::set<int> potatoSet;
    srand(328);
    std::mt19937 g(3);
    for (int i = 0; i < 50000; i++) {
        int sample = rand() % 2000000;
        if (turkeySet.find(sample) == turkeySet.end()) {
            turkeySet.insert(sample);
            potatoSet.insert(2000000 - sample);
            turkey.push_back(sample);
            potatos.push_back(2000000 - sample);
        }
    }
    std::shuffle(turkey.begin(), turkey.end(), g);
    std::shuffle(potatos.begin(), potatos.end(), g);
    
    TEST_PLATES(turkey, potatos, turkeySet, potatoSet, 2000000);
}
