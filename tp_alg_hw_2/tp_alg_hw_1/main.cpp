#include <iostream>
#include <cmath>
using namespace std;


struct dot
{
    int x;
    int y;
};


float CalcPolygonS(int& size, dot* verticies);
void ReadData(int& size, dot* verticies);
float CalcLen(dot& dot_1, dot& dot_2);
float CalcTriangleS(float* lens);



int main()
{
    int size;
    dot* verticies;

    cin >> size;
    verticies = new dot[size];

    ReadData(size, verticies);
    cout << CalcPolygonS(size, verticies);

    delete[] verticies;
    return 0;
}


void ReadData(int& size, dot* verticies)
{
    for(int i = 0; i < size; i++)
    {
        dot new_dot;
        cin >> new_dot.x;
        cin >> new_dot.y;

        verticies[i] = new_dot;
    }
}


float CalcPolygonS(int& size, dot* verticies)
{
    float* triangle_lens = new float[3];
    float polygon_s = 0;

    //construct triangles with one common vertex and add their area
    triangle_lens[0] = CalcLen(verticies[1], verticies[0]);

    for(int i = 1; i < size-1; i++)
    {
        triangle_lens[1] = CalcLen(verticies[i],verticies[i+1]);
        triangle_lens[2] = CalcLen(verticies[i+1],verticies[0]);

        polygon_s += CalcTriangleS(triangle_lens);
        triangle_lens[0] = triangle_lens[2];
    }

    delete [] triangle_lens;
    return polygon_s;
}


float CalcLen(dot& dot_1, dot& dot_2)
{
    float y = abs(dot_1.x - dot_2.x);
    float x = abs(dot_1.y - dot_2.y);

    float z = sqrt(pow(x,2) + pow(y,2));
    return z;
}


float CalcTriangleS(float* lens)
{
    float p = (lens[0] + lens[1] + lens[2])/2;
    float s = sqrt(p * (p - lens[0]) * (p - lens[1]) * (p - lens[2]));

    return s;
}
