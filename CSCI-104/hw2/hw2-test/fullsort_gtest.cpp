/*
CS 104: Homework 2 Problem 5, Spring 2018
fullsort_gtest.cpp
*/

#include <algorithm> 
#include <fstream>
#include <string>
#include <vector>
#include "gtest/gtest.h"

#include "../fullsort.cpp"

const std::string kTestInputPrefix{ "fullsort_input/input" };
const std::string kTestInputSuffix{ ".in" };

class FullsortTest : public testing::Test
{
public:
	void RunTest(int testNumber);

protected:
	FullsortTest() { }
	~FullsortTest() { }
	virtual void SetUp() { }
	virtual void TearDown() { }

private:
	bool LoadInput(int testNumber, Node*& head, std::vector<int>& input);
	void ComputeOutput(Node*& head);
	void ComputeSolution(std::vector<int>& solution);
	void VerifyOutput(const Node* head, const std::vector<int>& solution);
	void CleanUp(Node* head);
};

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(FullsortTest, Test1_HomeworkExample1)
{
	RunTest(1);
}

TEST_F(FullsortTest, Test2_HomeworkExample2)
{
	RunTest(2);
}

TEST_F(FullsortTest, Test3_HomeworkExample3)
{
	RunTest(3);
}

TEST_F(FullsortTest, Test4_HomeworkExample4)
{
	RunTest(4);
}

TEST_F(FullsortTest, Test5_EmptyList)
{
	RunTest(5);
}

TEST_F(FullsortTest, Test6_OneElementZero)
{
	RunTest(6);
}

TEST_F(FullsortTest, Test7_TwoElementsSorted)
{
	RunTest(7);
}

TEST_F(FullsortTest, Test8_TwoElementsUnsorted)
{
	RunTest(8);
}

TEST_F(FullsortTest, Test9_FiveIdenticalElements)
{
	RunTest(9);
}

TEST_F(FullsortTest, Test10_FirstElementUnsorted)
{
	RunTest(10);
}

TEST_F(FullsortTest, Test11_LastElementUnsorted)
{
	RunTest(11);
}

TEST_F(FullsortTest, Test12_SecondLastElementUnsorted)
{
	RunTest(12);
}

TEST_F(FullsortTest, Test13_MixedPositiveNegative)
{
	RunTest(13);
}

TEST_F(FullsortTest, Test14_OneHundredEvens)
{
	RunTest(14);
}

TEST_F(FullsortTest, Test15_OneThousandPrimes)
{
	RunTest(15);
}

void FullsortTest::RunTest(int testNumber)
{
	Node* head = nullptr;
	std::vector<int> solution;
	ASSERT_TRUE(LoadInput(testNumber, head, solution));
	ComputeOutput(head);
	ComputeSolution(solution);
	VerifyOutput(head, solution);
	CleanUp(head);
}

bool FullsortTest::LoadInput(int testNumber, Node*& head, std::vector<int>& input)
{
	std::ifstream ifs(kTestInputPrefix + std::to_string(testNumber) + kTestInputSuffix);
	if (ifs.fail())
	{
		return false;
	}

	Node* start = nullptr;
	int i = 0;

	while (ifs >> i)
	{
		input.emplace_back(i);
		Node* n = new Node;
		n->value = i;
		n->next = nullptr;

		if (head != nullptr)
		{
			head->next = n;
		}
		else
		{
			start = n;
		}
		head = n;
	}

	head = start;
	return true;
}

void FullsortTest::ComputeOutput(Node*& head)
{
	head = fullsort(head);
}

void FullsortTest::ComputeSolution(std::vector<int>& solution)
{
	std::sort(solution.begin(), solution.end());
}

void FullsortTest::VerifyOutput(const Node* head, const std::vector<int>& solution)
{
	for (size_t i = 0; i < solution.size(); ++i)
	{
		ASSERT_NE(nullptr, head);
		EXPECT_EQ(head->value, solution[i]);
		head = head->next;
	}
}

void FullsortTest::CleanUp(Node* head)
{
	while (head != nullptr)
	{
		Node* temp = head->next;
		delete head;
		head = temp;
	}
}