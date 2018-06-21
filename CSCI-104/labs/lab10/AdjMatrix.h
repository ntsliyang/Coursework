#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include "Graph.h"
#include <vector>

class AdjMatrix : public Graph
{
public:
	AdjMatrix(uint32_t vertexCount);
	virtual void addEdge(uint32_t u, uint32_t v, uint32_t w) override;
	virtual uint32_t getEdgeWeight(uint32_t u, uint32_t v) const override;
	virtual std::vector<uint32_t> getAllIncoming(uint32_t u) const override;
	virtual std::vector<uint32_t> getAllOutgoing(uint32_t u) const override;

private:
	std::vector<std::vector<uint32_t>> mEdges;
};

#endif