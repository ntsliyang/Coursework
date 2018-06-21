#include "AdjList.h"

AdjList::AdjList(uint32_t vertexCount)
	: mEdges(vertexCount)
{
}

void AdjList::addEdge(uint32_t u, uint32_t v, uint32_t w)
{
	mEdges[u].insert(std::make_pair(v, w));
}

uint32_t AdjList::getEdgeWeight(uint32_t u, uint32_t v) const
{
	// TODO
	for (auto it = mEdges[u].begin(); it != mEdges[u].end(); it++)
	{
		if (it->first == v)
			return it->second;
	}
	return 0;
}

std::vector<uint32_t> AdjList::getAllIncoming(uint32_t u) const
{
	std::vector<uint32_t> in;
	// TODO
	for (auto i = 0; i < mEdges.size(); i++)
	{
		auto it = mEdges[i].find(u);
		if (it != mEdges[i].end())
		{
			in.push_back(i);
		}
	}
	return in;
}

std::vector<uint32_t> AdjList::getAllOutgoing(uint32_t u) const
{
	std::vector<uint32_t> out;
	// TODO
	for (auto it = mEdges[u].begin(); it != mEdges[u].end(); ++it)
	{
		out.push_back(it->first);
	}
	return out;
}