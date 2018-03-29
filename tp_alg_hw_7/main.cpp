#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>
#include <vector>
#include <queue>
using namespace std;




void ReadStrings(vector<string>& buffer)
{
    ifstream file("input.txt");

    if (file.is_open())
    {
      while (file)
      {
          string str;
          getline(file, str);
          buffer.push_back(str);
      }

      file.close();
    }

    buffer.pop_back();
}


void PrintVector(const vector<string>& strings)
{
    int size = strings.size();

    for(int i = 0; i < size; i++)
        cout << strings[i] << endl;
}


char GetAtOrEnd(const string& str, const int& num)
{
    if(num <= str.length())
        return str[num];

    return '\0';
}


void CountSort(vector<string>& buffer, const int& start, const int& end /*included*/, const int& symbol_position)
{
    //symbol_num define on which symb in string array whould be sorted
    int window_size = end - start + 1;
    assert(end > start || window_size <= buffer.size());

    if(window_size > 1)
    {
        const int values_size = 256;
        int* values = new int[values_size];
        memset(values, 0, values_size * sizeof(int));

        for( int i = start; i <= end; i++)
            values[GetAtOrEnd(buffer[i], symbol_position)]++;

        for( int i = 1; i < values_size; i++)
            values[i] += values[i-1];

        string* sorted_buffer = new string[window_size];

        for(int i = end; i >= start; i--)
        {
            char index = GetAtOrEnd(buffer[i], symbol_position);
            sorted_buffer[--values[index]] = buffer[i];
        }

        int counter = 0;
        for(int i = start; i <= end; i++)
        {
            buffer[i] = sorted_buffer[counter];
            counter++;
        }

        delete [] sorted_buffer;
        delete [] values;
    }
}


void MsdSort(vector<string>& buffer)
{
    queue<int> borders;
    int max_length = 1;

    for(int i = 0; i < buffer.size(); i++)
        if(max_length < buffer[i].length())
            max_length = buffer[i].length();

    CountSort(buffer, 0, buffer.size()-1, 0);
    borders.push(0);
    borders.push(buffer.size());
    //PrintVector(buffer);

    //проходимся по буквам
    for(int i = 0; i < max_length-1; i++)
    {
        //проходимся по границам
        int borders_count = borders.size();
        for(int j = 0; j < borders_count-1; j++)
        {
            int border_start = borders.front();
            borders.push(border_start);
            borders.pop();

            //проходимся по словам в границах
            for(int k = border_start+1; k < borders.front(); k++)
                if(GetAtOrEnd(buffer[k], i) != GetAtOrEnd(buffer[k-1], i))
                {
                    CountSort(buffer, borders.back(), k-1, i+1);
                    borders.push(k);
                }

            CountSort(buffer, borders.back(), borders.front()-1, i+1);
        }

        borders.push(borders.front());
        borders.pop();
    }
}


int main()
{
    vector<string> strings;

    ReadStrings(strings);
    MsdSort(strings);
    PrintVector(strings);

    return 0;
}
