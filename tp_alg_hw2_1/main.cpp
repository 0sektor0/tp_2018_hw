#include <algorithm>
#include <iostream>
#include <string>
#include "assert.h"

using namespace std;



template<class T>
class HashTable
{
public:
    HashTable(const T& NIL, const T& DEL, int (*h1) (const T& key, const int& m), int (*h2) (const T& key, const int& m))
    {
        this->NIL = NIL;
        this->DEL = DEL;
        this->h1 = h1;
        this->h2 = h2;

        capacity = default_size;
        table = new T[capacity];
        len = 0;

        InitTable();
    }

    ~HashTable()
    {
        delete [] table;
    }

    bool Add(const T& key)
    {
        if (Fullness() >= 0.75)
            Resize();

        int hash1 = h1(key, capacity);
        int hash2 = h2(key, capacity);
        int del_pos = -1;

        for(int i = 0; i < capacity; i++)
        {
            int j = h(hash1, hash2, i);

            if(table[j] == NIL)
            {
                (del_pos == -1) ? table[j] = key : table[del_pos] = key;
                len++;
                return 1;
            }
            else if (table[j] == key)
                return 0;
            else if (table[j] == DEL)
                del_pos = j;
        }

        if(del_pos >= 0)
        {
            table[del_pos] = key;
            len++;
            return 1;
        }

        return 0;
    }

    bool Delete(const T& key)
    {
        int hash1 = h1(key, capacity);
        int hash2 = h2(key, capacity);

        for(int i = 0; i < capacity; i++)
        {
            int j = h(hash1, hash2, i);

            if(table[j] == NIL)
                return 0;
            else if(table[j] == key)
            {
                table[j] = DEL;
                len--;
                return 1;
            }
        }

        return 0;
    }

    bool Has(const T& key)
    {
        int hash1 = h1(key, capacity);
        int hash2 = h2(key, capacity);

        for(int i = 0; i < capacity; i++)
        {
            int j = h(hash1, hash2, i);

            if(table[j] == NIL)
                return 0;
            else if(table[j] == key)
                return 1;
        }

        return 0;
    }

    const int& Length()
    {
        return len;
    }


private:
    const int default_size = 8;
    int (*h1) (const T& key, const int& m);
    int (*h2) (const T& key, const int& m);
    int capacity;
    T* table;
    int len;
    T NIL;
    T DEL;

    void Resize()
    {
        int capacity_old = capacity * 2;
        swap(capacity, capacity_old);
        len = 0;

        T* table_old = new T[capacity];
        swap(table, table_old);
        InitTable();

        for(int i = 0; i < capacity_old; i++)
            if(table_old[i] != NIL && table_old[i] != DEL)
                Add(table_old[i]);

        delete [] table_old;
    }

    int h(const int& hash1, const int& hash2, const int& i)
    {
        return (hash1 + i*hash2) % capacity;
    }

    double Fullness()
    {
        return (double)len / (double)capacity;
    }

    void InitTable()
    {
        for(int i = 0; i < capacity; i++)
            table[i] = NIL;
    }
};


int StrHash1(const std::string& str, const int& m)
{
    assert(str.length()>0);

    const int a = 101;
    int hash = 0;

    for(int i =0; i < str.length(); i++)
        hash = (hash * a + str[i]) % m;

    return hash;
}


int StrHash2(const std::string& str, const int& m)
{
    assert(str.length()>0);

    const int a = 127;
    int hash = 0;

    for(int i =0; i < str.length(); i++)
        hash = (hash * a + str[i]) % m;

    return ((2*hash) + 1) % m;
}


int IntHash1(const int& v, const int& m)
{
    return v%m;
}


int IntHash2(const int& v, const int& m)
{
    int hash = v%m;
    return ((2*hash) + 1) % m;
}


int main()
{
    HashTable<string> ht("", " ", StrHash1, StrHash2);
    char command = 0;
    string key;

    while( cin >> command >> key )
        switch( command )
        {
        case '?':
            cout << (ht.Has(key) ? "OK" : "FAIL" ) << endl;
            break;
        case '+':
            cout << (ht.Add(key) ? "OK" : "FAIL" ) << endl;
            break;
        case '-':
            cout << (ht.Delete(key) ? "OK" : "FAIL" ) << endl;
            break;
        default:
            break;
        }

    /*HashTable<int> ht(0, -1, IntHash1, IntHash2);
    char command = 0;
    int key;

    while( cin >> command >> key )
        switch( command )
        {
        case '?':
            cout << (ht.Has(key) ? "OK" : "FAIL" ) << endl;
            break;
        case '+':
            cout << (ht.Add(key) ? "OK" : "FAIL" ) << endl;
            break;
        case '-':
            cout << (ht.Delete(key) ? "OK" : "FAIL" ) << endl;
            break;
        default:
            break;
        }*/

    /**
     *вычислять хэш заранее
     * не вставлять в del
     **/
    return 0;
}
