#include <vector>
#include <iostream>
#include "carcgraph.h"
#include "csetgraph.h"
#include "clistgraph.h"
#include "cmatrixgraph.h"

using namespace std;


int main()
{
    CListGraph lg(4);
    vector<int> next_vertices_lg;
    vector<int> prev_vertices_lg;
    lg.AddEdge(0,0);
    lg.AddEdge(0,1);
    lg.AddEdge(2,0);
    lg.AddEdge(2,3);
    lg.AddEdge(3,2);
    lg.AddEdge(3,1);

    CMatrixGraph mg(&lg);
    vector<int> next_vertices_mg;
    vector<int> prev_vertices_mg;

    lg.AddEdge(1,3);
    mg.AddEdge(1,3);

    lg.GetNextVertices(2, next_vertices_lg);
    lg.GetPrevVertices(2, prev_vertices_lg);
    mg.GetNextVertices(2, next_vertices_mg);
    mg.GetPrevVertices(2, prev_vertices_mg);

    if(next_vertices_mg == next_vertices_lg)
        cout << "[OK] NEXT matrix list\n";
    else
        cout << "[FAIL] NEXT matrix list\n";

    if(prev_vertices_mg == prev_vertices_lg)
        cout << "[OK] PREV matrix list\n";
    else
        cout << "[FAIL] PREV matrix list\n";


    CSetGraph sg(&mg);
    vector<int> next_vertices_sg;
    vector<int> prev_vertices_sg;

    mg.AddEdge(2,2);
    sg.AddEdge(2,2);

    sg.GetNextVertices(2, next_vertices_sg);
    sg.GetPrevVertices(2, prev_vertices_sg);
    mg.GetNextVertices(2, next_vertices_mg);
    mg.GetPrevVertices(2, prev_vertices_mg);

    if(next_vertices_mg == next_vertices_sg)
        cout << "[OK] NEXT matrix set\n";
    else
        cout << "[FAIL] NEXT matrix set\n";

    if(prev_vertices_mg == prev_vertices_sg)
        cout << "[OK] PREV matrix set\n";
    else
        cout << "[FAIL] PREV matrix set\n";


    CArcGraph cg(&mg);
    vector<int> next_vertices_cg;
    vector<int> prev_vertices_cg;

    mg.AddEdge(3,3);
    cg.AddEdge(3,3);

    cg.GetNextVertices(3, next_vertices_cg);
    cg.GetPrevVertices(3, prev_vertices_cg);
    mg.GetNextVertices(3, next_vertices_mg);
    mg.GetPrevVertices(3, prev_vertices_mg);

    if(next_vertices_mg == next_vertices_cg)
        cout << "[OK] NEXT matrix pair\n";
    else
        cout << "[FAIL] NEXT matrix pair\n";

    if(prev_vertices_mg == prev_vertices_cg)
        cout << "[OK] PREV matrix pair\n";
    else
        cout << "[FAIL] PREV matrix pair\n";

    return 0;
}
