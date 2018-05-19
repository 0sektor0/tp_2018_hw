#ifndef CSETGRAPH_H
#define CSETGRAPH_H

#include <set>
#include "igraph.h"


class CSetGraph : public IGraph
{
public:
    int VerticesCount();
    CSetGraph(const int&);
    CSetGraph(IGraph*);
    void AddEdge(const int&, const int&);
    void GetNextVertices(const int&, std::vector<int>&);
    void GetPrevVertices(const int&, std::vector<int>&);
    virtual ~CSetGraph() {}


private:
    vector<set<int>> vertices_sets_list;
};

#endif // CSETGRAPH_H
