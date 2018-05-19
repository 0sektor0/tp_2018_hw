#ifndef CMATRIXGRAPH_H
#define CMATRIXGRAPH_H

#include "igraph.h"


class CMatrixGraph : public IGraph
{
public:
    int VerticesCount();
    CMatrixGraph(const int&);
    CMatrixGraph(IGraph*);
    void AddEdge(const int&, const int&);
    void GetNextVertices(const int&, std::vector<int>&);
    void GetPrevVertices(const int&, std::vector<int>&);
    virtual ~CMatrixGraph();


private:
    bool** vertices_matrix;
    int size;
};

#endif // CMATRIXGRAPH_H
