#include "clistgraph.h"



CListGraph::CListGraph(const int& vertices_count)
{
    vertices_adjacency_list = vector<vector<int>>(vertices_count, vector<int>());
}


CListGraph::CListGraph(IGraph* graph)
{
    int size = graph->VerticesCount();
    vertices_adjacency_list = vector<vector<int>>(size, vector<int>());

    for(int i = 0; i < size; i++)
    {
        vector<int> i_vertices;
        graph->GetNextVertices(i, i_vertices);

        for(int next : i_vertices)
            AddEdge(i, next);
    }
}


int CListGraph::VerticesCount()
{
    return vertices_adjacency_list.size();
}


bool  CListGraph::IsConnected(const int& from, const int& to)
{
    for(int next : vertices_adjacency_list[from])
        if(next == to)
            return true;

    return false;
}


void CListGraph::AddEdge(const int& from, const int& to)
{
    int size = VerticesCount();

    if(from < size && to < size)
        if(!IsConnected(from, to))
            vertices_adjacency_list[from].push_back(to);
}


void CListGraph::GetNextVertices(const int& vertex, std::vector<int>& vertices)
{
    if (vertex < VerticesCount())
        vertices = vector<int>(vertices_adjacency_list[vertex]);
    else
        vertices.resize(0);
}


void CListGraph::GetPrevVertices(const int& vertex, std::vector<int>& vertices)
{
    vertices.resize(0);
    int size = VerticesCount();

    if (vertex >= size)
        return;

    for(int i = 0; i < size; i++)
        if(IsConnected(i, vertex))
            vertices.push_back(i);
}
