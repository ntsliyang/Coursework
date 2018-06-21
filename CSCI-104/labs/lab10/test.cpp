#include "AdjList.h"
#include "AdjMatrix.h"
#include <algorithm>
#include "EdgeSet.h"
#include <fstream>
#include "Graph.h"
#include "gtest/gtest.h"

class GraphTest : public testing::Test 
{
protected:
	virtual void SetUp() override;
	void AddEdges(Graph& g);
	bool Contains(const std::vector<uint32_t>& v, uint32_t n);
	void TestEdgeWeight(const Graph& g);
	void TestIncomingEdge(const Graph& g);
	void TestOutgoingEdge(const Graph& g);

	std::ifstream mGraphFile;
	uint32_t mVertexCount;
	uint32_t mEdgeCount;
};

void GraphTest::SetUp()
{
	mGraphFile.open("input.txt");
	mGraphFile >> mVertexCount >> mEdgeCount;
}

void GraphTest::AddEdges(Graph& g)
{
	for (uint32_t i = 0; i < mEdgeCount; ++i)
	{
		uint32_t u, v, w;
		mGraphFile >> u >> v >> w;
		g.addEdge(u, v, w);
	}
}

bool GraphTest::Contains(const std::vector<uint32_t>& v, uint32_t n)
{
	return std::find(v.begin(), v.end(), n) != v.end();
}

void GraphTest::TestEdgeWeight(const Graph& g)
{
	EXPECT_EQ(1, g.getEdgeWeight(0, 1));
	EXPECT_EQ(8, g.getEdgeWeight(0, 3));
	EXPECT_EQ(7, g.getEdgeWeight(0, 4));
	EXPECT_EQ(1, g.getEdgeWeight(1, 2));
	EXPECT_EQ(1, g.getEdgeWeight(2, 5));
	EXPECT_EQ(25, g.getEdgeWeight(3, 4));
	EXPECT_EQ(5, g.getEdgeWeight(4, 5));
	EXPECT_EQ(9, g.getEdgeWeight(1, 3));
	EXPECT_EQ(20, g.getEdgeWeight(1, 0));
	
	EXPECT_EQ(0, g.getEdgeWeight(0, 2));
	EXPECT_EQ(0, g.getEdgeWeight(0, 5));
	EXPECT_EQ(0, g.getEdgeWeight(4, 3));
}

void GraphTest::TestIncomingEdge(const Graph& g)
{
	std::vector<uint32_t> in = g.getAllIncoming(5);
	EXPECT_TRUE(Contains(in, 2));
	EXPECT_TRUE(Contains(in, 4));
	EXPECT_FALSE(Contains(in, 0));
	EXPECT_FALSE(Contains(in, 1));
	EXPECT_FALSE(Contains(in, 3));
	EXPECT_FALSE(Contains(in, 5));
}

void GraphTest::TestOutgoingEdge(const Graph& g)
{
	std::vector<uint32_t> out = g.getAllOutgoing(1);
	EXPECT_TRUE(Contains(out, 0));
	EXPECT_TRUE(Contains(out, 2));
	EXPECT_TRUE(Contains(out, 3));
	EXPECT_FALSE(Contains(out, 1));
	EXPECT_FALSE(Contains(out, 4));
	EXPECT_FALSE(Contains(out, 5));
}

TEST_F(GraphTest, EdgeSet_EdgeWeight) 
{
	EdgeSet g;
	AddEdges(g);
	TestEdgeWeight(g);
}

TEST_F(GraphTest, EdgeSet_IncomingEdge) 
{
	EdgeSet g;
	AddEdges(g);
	TestIncomingEdge(g);
}

TEST_F(GraphTest, EdgeSet_OutgoingEdge) 
{
	EdgeSet g;
	AddEdges(g);
	TestOutgoingEdge(g);
}

TEST_F(GraphTest, AdjMatrix_EdgeWeight) 
{
	AdjMatrix g(mVertexCount);
	AddEdges(g);
	TestEdgeWeight(g);
}

TEST_F(GraphTest, AdjMatrix_IncomingEdge) 
{
	AdjMatrix g(mVertexCount);
	AddEdges(g);
	TestIncomingEdge(g);
}

TEST_F(GraphTest, AdjMatrix_OutgoingEdge) 
{
	AdjMatrix g(mVertexCount);
	AddEdges(g);
	TestOutgoingEdge(g);
}

TEST_F(GraphTest, AdjList_EdgeWeight) 
{
	AdjList g(mVertexCount);
	AddEdges(g);
	TestEdgeWeight(g);
}

TEST_F(GraphTest, AdjList_IncomingEdge) 
{
	AdjList g(mVertexCount);
	AddEdges(g);
	TestIncomingEdge(g);
}

TEST_F(GraphTest, AdjList_OutgoingEdge) 
{
	AdjList g(mVertexCount);
	AddEdges(g);
	TestOutgoingEdge(g);
}