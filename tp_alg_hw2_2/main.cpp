#include "assert.h"
#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;


template<class T>
struct BstNode
{
    BstNode(const T& v)
    {
        data = v;
        left = nullptr;
        right = nullptr;
    }

    T data;
    BstNode<T>* left;
    BstNode<T>* right;
};


template<class T>
class Bst
{
public:
    Bst(bool (*meq) (const T&, const T&))
    {
        this->meq = meq;
        this->root = nullptr;
        this->len = 0;
    }

    ~Bst()
    {
        if (root)
        {
            stack<BstNode<T>*> dBstNodes;
            BstNode<T>* cBstNode;

            dBstNodes.push(root);
            while(!dBstNodes.empty())
            {
                cBstNode = dBstNodes.top();
                dBstNodes.pop();

                if(cBstNode->left)
                    dBstNodes.push(cBstNode->left);

                if(cBstNode->right)
                    dBstNodes.push(cBstNode->right);

                delete cBstNode;
            }
        }
    }

    void Add(const T& n)
    {
        if(root != nullptr)
        {
            BstNode<T>* cBstNode = root;

            for(;;)
            {
                if(meq(n, cBstNode->data))
                {
                    if(cBstNode->right == nullptr)
                    {
                        cBstNode->right = new BstNode<T>(n);
                        break;
                    }
                    else
                        cBstNode = cBstNode->right;
                }
                else
                {
                    if(cBstNode->left == nullptr)
                    {
                        cBstNode->left = new BstNode<T>(n);
                        break;
                    }
                    else
                        cBstNode = cBstNode->left;
                }
            }
        }
        else
        {
            root = new BstNode<T>(n);
        }
    }

    vector<T> PostOrder()
    {
        assert(root);
        vector<T> vBstNodes;
        stack<BstNode<T>*> lBstNodes;
        BstNode<T>* cBstNode;

        lBstNodes.push(root);
        while(!lBstNodes.empty())
        {
            cBstNode = lBstNodes.top();
            lBstNodes.pop();

            for(;;)
            {
                vBstNodes.push_back(cBstNode->data);

                if(cBstNode->left != nullptr)
                    lBstNodes.push(cBstNode->left);

                if(cBstNode->right == nullptr)
                    break;

                cBstNode = cBstNode->right;
            }
        }

        return vBstNodes;
    }


private:
    bool (*meq) (const T&, const T&);
    BstNode<T>* root;
    int len;
};


bool meq(const int& f1, const int& f2)
{
    return f1 >= f2;
}


int main()
{
    Bst<int> tree(meq);
    int counter;
    int data;

    cin >> counter;
    for(int i = 0; i < counter; i++)
    {
        cin >> data;
        tree.Add(data);
    }

    vector<int> vn = tree.PostOrder();
    for(int i = vn.size()-1; i >=0; i--)
        cout << vn[i] << " ";

    return 0;
}
