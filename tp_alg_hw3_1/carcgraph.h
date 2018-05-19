#ifndef CARCGRAPH_H
#define CARCGRAPH_H

#include "igraph.h"
#include <utility>


class CArcGraph : public IGraph
{
public:
    int VerticesCount();
    CArcGraph(const int&);
    CArcGraph(IGraph*);
    void AddEdge(const int&, const int&);
    void GetNextVertices(const int&, std::vector<int>&);
    void GetPrevVertices(const int&, std::vector<int>&);
    virtual ~CArcGraph() {}


private:
    vector<pair<int,int>> vertices_pairs_list;
    int vertices_count;
};


#endif // CARCGRAPH_H
