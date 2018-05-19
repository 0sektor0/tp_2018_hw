#include "carcgraph.h"



CArcGraph::CArcGraph(const int& vertices_count)
{
    this->vertices_count = vertices_count;
}


CArcGraph::CArcGraph(IGraph* graph)
{
    vertices_count = graph->VerticesCount();

    for(int i = 0; i < vertices_count; i++)
    {
        vector<int> next;
        graph->GetNextVertices(i, next);

        for(int vertex : next)
            vertices_pairs_list.push_back(pair<int,int>(i, vertex));
    }
}


int CArcGraph::VerticesCount()
{
    return vertices_count;
}


void CArcGraph::AddEdge(const int& from, const int& to)
{
    if(from >= vertices_count || to >= vertices_count)
        return;

    pair<int,int> new_pair = pair<int,int>(from, to);

    for(pair<int,int> existing_pair : vertices_pairs_list)
        if(existing_pair == new_pair)
            return;

    vertices_pairs_list.push_back(new_pair);
}


void CArcGraph::GetNextVertices(const int& vertex, std::vector<int>& vertices)
{
    vertices.resize(0);

    if(vertex >= vertices_count)
        return;

    for(pair<int,int> pair : vertices_pairs_list)
        if(pair.first == vertex)
            vertices.push_back(pair.second);
}


void CArcGraph::GetPrevVertices(const int& vertex, std::vector<int>& vertices)
{
    vertices.resize(0);

    if(vertex >= vertices_count)
        return;

    for(pair<int,int> pair : vertices_pairs_list)
        if(pair.second == vertex)
            vertices.push_back(pair.first);
}






























