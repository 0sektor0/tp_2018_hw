#include "csetgraph.h"



CSetGraph::CSetGraph(const int& size)
{
    vertices_sets_list = vector<set<int>>(size, set<int>());
}


CSetGraph::CSetGraph(IGraph* graph)
{
    int size = graph->VerticesCount();
    vertices_sets_list = vector<set<int>>(size, set<int>());

    for(int i = 0; i < size; i++)
    {
        vector<int> next_vertices;
        graph->GetNextVertices(i, next_vertices);

        for(int vertex : next_vertices)
            vertices_sets_list[i].insert(vertex);
    }
}


int CSetGraph::VerticesCount()
{
    return vertices_sets_list.size();
}


void CSetGraph::AddEdge(const int& from, const int& to)
{
    int size = vertices_sets_list.size();

    if(from < size && to < size)
        vertices_sets_list[from].insert(to);
}


void CSetGraph::GetNextVertices(const int& vertex, std::vector<int>& vertices)
{
    int size = vertices_sets_list.size();
    vertices.resize(0);

    if(vertex >= size)
        return;

    for(int next : vertices_sets_list[vertex])
        vertices.push_back(next);
}


void CSetGraph::GetPrevVertices(const int& vertex, std::vector<int>& vertices)
{
    int size = vertices_sets_list.size();
    vertices.resize(0);

    if(vertex >= size)
        return;

    for(int i = 0; i < size; i++)
        if(vertices_sets_list[i].find(vertex) != vertices_sets_list[i].end())
            vertices.push_back(i);
}
























