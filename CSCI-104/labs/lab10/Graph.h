#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>
#include <vector>

class Graph
{
public:
	
	/* add an edge from u to v with weight w
	*/
	virtual void addEdge(uint32_t u, uint32_t v, uint32_t w) = 0;
	
	/* return the edge weight if there's an edge from u to v.
		 return 0 otherwise.
	*/
	virtual uint32_t getEdgeWeight(uint32_t u, uint32_t v) const = 0;

	/* return all vertices v such that there's an edge
		 from v to u.
	*/
	virtual std::vector<uint32_t> getAllIncoming(uint32_t u) const = 0;

	/* return all vertices v such that there's an edge
		 from u to v.
	*/
	virtual std::vector<uint32_t> getAllOutgoing(uint32_t u) const = 0;

	virtual ~Graph(){}
};

#endif