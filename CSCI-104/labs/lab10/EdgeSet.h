#ifndef EDGESET_H
#define EDGESET_H

#include "Graph.h"
#include <map>

class EdgeSet : public Graph
{
public:
	virtual void addEdge(uint32_t u, uint32_t v, uint32_t w) override;
	virtual uint32_t getEdgeWeight(uint32_t u, uint32_t v) const override;
	virtual std::vector<uint32_t> getAllIncoming(uint32_t u) const override;
	virtual std::vector<uint32_t> getAllOutgoing(uint32_t u) const override;

private:
	struct Edge
	{
		Edge(uint32_t from, uint32_t to) : mFrom(from), mTo(to) {}
		bool operator<(const Edge& rhs) const;
		
		uint32_t mFrom;
		uint32_t mTo;
	};

private:
	std::map<Edge, uint32_t> mEdges;
};

#endif