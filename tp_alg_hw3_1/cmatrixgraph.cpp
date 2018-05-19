#include "cmatrixgraph.h"



CMatrixGraph::CMatrixGraph(const int& vertices_count)
{
    size = vertices_count;
    vertices_matrix = new bool*[size];

    for(int i = 0; i < size; i++)
        vertices_matrix[i] = new bool[size];
}


CMatrixGraph::CMatrixGraph(IGraph* graph)
{
    size = graph->VerticesCount();
    vertices_matrix = new bool*[size];

    for(int i = 0; i < size; i++)
    {
        vertices_matrix[i] = new bool[size];
        vector<int> next_vertices;
        graph->GetNextVertices(i, next_vertices);

        for(int vertex : next_vertices)
            vertices_matrix[i][vertex] = true;
    }
}


int CMatrixGraph::VerticesCount()
{
    return size;
}


void CMatrixGraph::AddEdge(const int& from, const int& to)
{
    if(from < size && to < size)
        vertices_matrix[from][to] = true;
}


void CMatrixGraph::GetNextVertices(const int& vertex, std::vector<int>& vertices)
{
    vertices.resize(0);

    if(vertex >= size)
        return;

    for(int i = 0; i < size; i++)
        if(vertices_matrix[vertex][i])
            vertices.push_back(i);
}


void CMatrixGraph::GetPrevVertices(const int& vertex, std::vector<int>& vertices)
{
    vertices.resize(0);

    if(vertex >= size)
        return;

    for(int i = 0; i < size; i++)
        if(vertices_matrix[i][vertex])
            vertices.push_back(i);
}


CMatrixGraph::~CMatrixGraph()
{
    for(int i = 0; i < size; i++)
        delete [] vertices_matrix[i];
    delete [] *vertices_matrix;
}












