#include "EdgeSet.h"

void EdgeSet::addEdge(uint32_t u, uint32_t v, uint32_t w)
{
	mEdges.insert(std::make_pair(Edge(u, v), w));
}

uint32_t EdgeSet::getEdgeWeight(uint32_t u, uint32_t v) const
{
	std::map<Edge, uint32_t>::const_iterator it = mEdges.find(Edge(u, v));
	if (it == mEdges.end())
	{
		return 0;
	}
	else
	{
		return it->second;
	}
	return 0;
}

std::vector<uint32_t> EdgeSet::getAllIncoming(uint32_t u) const
{
	std::vector<uint32_t> in;
	for (std::map<Edge, uint32_t>::const_iterator it = mEdges.begin();
		 it != mEdges.end(); ++it)
	{
		if (it->first.mTo == u)
		{
			in.push_back(it->first.mFrom);
		}
	}
	return in;
}

std::vector<uint32_t> EdgeSet::getAllOutgoing(uint32_t u) const
{
	std::vector<uint32_t> out;
	for (std::map<Edge, uint32_t>::const_iterator it = mEdges.begin();
		 it != mEdges.end(); ++it)
	{
		if (it->first.mFrom == u)
		{
			out.push_back(it->first.mTo);
		}
	}
	return out;
}

bool EdgeSet::Edge::operator<(const EdgeSet::Edge &rhs) const
{
	return mFrom < rhs.mFrom || (mFrom == rhs.mFrom && mTo < rhs.mTo);
}