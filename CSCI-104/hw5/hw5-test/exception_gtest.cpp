#include <algorithm> 
#include <fstream>
#include <string>
#include <vector>
#include "gtest/gtest.h"

// #include "../LengthMismatch.h"
#include "../LengthMismatch.cpp"

class LengthMismatchTest : public testing::Test
{
public:
	void RunTest(int testNumber);

protected:
	LengthMismatchTest() { }
	~LengthMismatchTest() { }
};

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

/*
 * Test A Simple Construction
 * */
TEST_F(LengthMismatchTest, Test1)
{
    LengthMismatch lmm(0, 0);    
}

/*
 * Test with the what function
 * */
TEST_F(LengthMismatchTest, Test2)
{
    LengthMismatch lmm(0, 2); 
    std::string what = lmm.what();
    EXPECT_EQ(what, "Input data structures have lengths 0 and 2");  
}

/*
 * Test with another length 
 * */
TEST_F(LengthMismatchTest, Test3)
{
    LengthMismatch lmm(200, 328); 
    std::string what = lmm.what();
    EXPECT_EQ(what, "Input data structures have lengths 200 and 328");     
}

/*
 * LengthMismatch should be a std::exception
 * */
TEST_F(LengthMismatchTest, Test4)
{
    LengthMismatch * lmm = new LengthMismatch(200, 328); 
    if(std::exception* v = dynamic_cast<LengthMismatch*>(lmm)) {
        EXPECT_EQ(v, v);
    } else {
        EXPECT_EQ("LengthMismatch", "Not instance of std::exception");
    }
}

/*
 * Cast it into std::exception should still have the same what() output
 * */
TEST_F(LengthMismatchTest, Test5)
{
    LengthMismatch * lmm = new LengthMismatch(200, 328); 
    if(std::exception* v = dynamic_cast<LengthMismatch*>(lmm)) {
        std::string what = v->what();
        EXPECT_EQ(what, "Input data structures have lengths 200 and 328");     
    } else {
        EXPECT_EQ("LengthMismatch", "Not instance of std::exception");
    }
}