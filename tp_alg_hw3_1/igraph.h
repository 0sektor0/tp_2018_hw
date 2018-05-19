#ifndef IGRAPH_H
#define IGRAPH_H

#include <iostream>
#include <vector>

using namespace std;


struct IGraph
{
    virtual ~IGraph() {}
    virtual int VerticesCount() = 0;
    virtual void AddEdge(const int& from, const int& to) = 0;
    virtual void GetNextVertices(const int& vertex, std::vector<int>& vertices) = 0;
    virtual void GetPrevVertices(const int& vertex, std::vector<int>& vertices) = 0;
};

#endif // IGRAPH_H
