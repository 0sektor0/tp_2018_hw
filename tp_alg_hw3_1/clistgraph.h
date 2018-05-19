#ifndef CLISTGRAPH_H
#define CLISTGRAPH_H

#include "igraph.h"


class CListGraph : public IGraph
{
public:
    int VerticesCount();
    CListGraph(const int&);
    CListGraph(IGraph*);
    void AddEdge(const int&, const int&);
    void GetNextVertices(const int&, std::vector<int>&);
    void GetPrevVertices(const int&, std::vector<int>&);
    virtual ~CListGraph() {}


private:
    vector<vector<int>> vertices_adjacency_list;

    bool IsConnected(const int&, const int&);
};

#endif // CLISTGRAPH_H
