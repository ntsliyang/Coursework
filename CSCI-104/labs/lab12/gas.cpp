#include <fstream>
#include <limits>
#include <map>
#include <vector>

struct Edge
{
	Edge(uint32_t from, uint32_t to, uint32_t weight)
		: mFrom(from), mTo(to), mWeight(weight) {}
	uint32_t mFrom;
	uint32_t mTo;
	int mWeight;
};

using Graph = std::vector<Edge>;
using Distances = std::vector<int>;
using Predecessors = std::vector<uint32_t>;

uint32_t readGraph(std::istream &input, Graph &graph)
{
	uint32_t vertCount = 0;
	uint32_t edgeCount = 0;
	input >> vertCount >> edgeCount;

	for (uint32_t i = 0; i < edgeCount; ++i)
	{
		uint32_t u, v;
		int w;
		input >> u >> v >> w;
		graph.push_back(Edge(u, v, w));
	}
	return vertCount;
}

void writePath(std::ostream &output, const Predecessors &predecessors, uint32_t v)
{
	// TODO
	if (predecessors[v] == -1)
	{
		output << v << " ";
	}
	else
	{
		writePath(output, predecessors, predecessors[v]);
		output << v << " ";
	}
}

void writeOutput(std::ostream &output, bool cycle, const Distances &distances, const Predecessors &predecessors)
{
	if (cycle)
	{
		output << "error: negative-gas-consumption cycle" << std::endl;
	}
	else if (distances[distances.size() - 1] == std::numeric_limits<int>::max())
	{
		output << "error: no path to campsite" << std::endl;
	}
	else
	{
		output << "path: ";
		writePath(output, predecessors, distances.size() - 1);
		output << std::endl;
		output << "cost: " << distances[distances.size() - 1] << std::endl;
	}
}

bool BellmanFord(const Graph &graph, Distances &distances, Predecessors &predecessors)
{
	// TODO
	distances[0] = 0;
	predecessors[0] = -1;
	for (auto i = 0; i < distances.size(); i++)
	{ // for i from 0 to |V| - 1:
		for (auto j = 0; j < graph.size(); j++)
		{
			if (distances[graph[j].mFrom] + graph[j].mWeight < distances[graph[j].mTo])
			{
				if (distances[graph[j].mFrom] + graph[j].mWeight < 0) {
					distances[graph[j].mTo] = std::numeric_limits<int>::max();
				}
				else distances[graph[j].mTo] = distances[graph[j].mFrom] + graph[j].mWeight;
				predecessors[graph[j].mTo] = graph[j].mFrom;
			}
		}
	}
	for (auto i = 0; i < graph.size(); i++)
	{
		if (distances[graph[i].mFrom] + graph[i].mWeight < 0) return false;
		if (distances[graph[i].mFrom] + graph[i].mWeight < distances[graph[i].mTo])
		{
			return true;
		}
	}

	return false;
}

int main(int argc, char *argv[])
{
	// read input
	Graph graph;
	std::ifstream input(argv[1]);
	uint32_t vertCount = readGraph(input, graph);
	input.close();

	// find shortest path
	Distances distances(vertCount, std::numeric_limits<int>::max());
	// initialize all distances to be positive infinity
	Predecessors predecessors(vertCount, 0);
	// initialzie all predecessors to be None
	bool cycle = BellmanFord(graph, distances, predecessors);

	// write output
	std::ofstream output(argv[2]);
	writeOutput(output, cycle, distances, predecessors);
	output.close();

	return 0;
}
