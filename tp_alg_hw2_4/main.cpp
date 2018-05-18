#include <iostream>
#include <assert.h>
#include <stack>
#include <cmath>

using namespace std;



template<class T>
struct Node
{
    unsigned int nodes_count;
    unsigned int height;
    Node<T>* right;
    Node<T>* left;
    T key;

    Node(const T& k)
    {
        key = k;
        height = 1;
        nodes_count = 1;
        left = right = nullptr;
    }
};


template<class T>
class AvlTree
{
public:
    AvlTree(bool(*comp)(const T&, const T&))
    {
        len = 0;
        root = nullptr;
        this->comp = comp;
    }

    int Add(const T& key)
    {
        int index = 0;

        root = Insert(root, key);//, index);
        len++;

        return index;
    }

    int FindKeyIndex(const T& key)
    {
        return FindKeyIndex(key, root, NodesCount(root->left));
    }

    void Delete(const int& index)
    {
        Node<T>* n = FindIndex(root, index, 1);
        if(n!=nullptr)
            root = Remove(root, n->key);
    }

    ~AvlTree()
    {
        if (root != nullptr)
        {
            stack<Node<T>*> nodes;
            Node<T>* cnode;

            nodes.push(root);
            while(!nodes.empty())
            {
                cnode = nodes.top();
                nodes.pop();

                if(cnode->left)
                    nodes.push(cnode->left);

                if(cnode->right)
                    nodes.push(cnode->right);

                delete cnode;
            }
        }
    }

private:
    bool(*comp)(const T&, const T&);
    Node<T>* root;
    int len;

    unsigned int NodeHeight(Node<T>* n)
    {
        return n!=nullptr ? n->height : 0;
    }

    int NodesCount(Node<T>* n)
    {
        return n!=nullptr ? n->nodes_count : 0;
    }

    int Bfactor(Node<T>* n)
    {
        return NodeHeight(n->right)-NodeHeight(n->left);
    }

    void FixHeight(Node<T>* n)
    {
        unsigned int lnh = NodeHeight(n->left);
        unsigned int rnh = NodeHeight(n->right);
        n->height = (lnh>rnh?lnh:rnh)+1;
    }

    void FixNodesCounter(Node<T>* n)
    {
        n->nodes_count = 1 + NodesCount(n->left) + NodesCount(n->right);
    }

    int FindKeyIndex(const T& key, const Node<T>* node, int current_index)
    {
        if(node==nullptr)
            return -1;
        else if(node->key == key)
            return current_index;
        else if(comp(key, node->key))
            return FindKeyIndex(key, node->right, current_index + 1 + NodesCount(node->right->left));
        else
            return FindKeyIndex(key, node->left, current_index - 1 - NodesCount(node->left->right));
    }

    Node<T>* RotateR(Node<T>* n)
    {
        Node<T>* l = n->left;
        n->left = l->right;
        l->right = n;

        FixHeight(n);
        FixNodesCounter(n);

        FixHeight(l);
        FixNodesCounter(l);

        return l;
    }

    Node<T>* RotateL(Node<T>* n)
    {
        Node<T>* r = n->right;
        n->right = r->left;
        r->left = n;

        FixHeight(n);
        FixNodesCounter(n);

        FixHeight(r);
        FixNodesCounter(r);

        return r;
    }

    Node<T>* Balance(Node<T>* n)
    {
        FixHeight(n);
        FixNodesCounter(n);

        if( Bfactor(n)>=2 )
        {
            if( Bfactor(n->right) < 0 )
                n->right = RotateR(n->right);
            return RotateL(n);
        }

        if( Bfactor(n)<=-2 )
        {
            if( Bfactor(n->left) > 0  )
                n->left = RotateL(n->left);
            return RotateR(n);
        }

        return n;
    }

    Node<T>* Insert(Node<T>* root, const T& key)//, int& index)
    {
        if( root == nullptr )
            return new Node<T>(key);

        if(!comp(key, root->key))
            root->left = Insert(root->left, key);
        else
            root->right = Insert(root->right, key);

        return Balance(root);
    }

    Node<T>* FindMin(Node<T>* n)
    {
        return n->left!=nullptr ? FindMin(n->left) : n;
    }

    Node<T>* RemoveMin(Node<T>* n)
    {
        if( n->left == nullptr )
            return n->right;
        n->left = RemoveMin(n->left);
        return Balance(n);
    }

    Node<T>* Remove(Node<T>* n, const T& k)
    {
        if( n == nullptr )
            return nullptr;
        if( !comp(k,n->key) )
            n->left = Remove(n->left,k);
        else if(k == n->key)
        {
            Node<T>* q = n->left;
            Node<T>* r = n->right;
            delete n;
            if( !r )
                return q;

            Node<T>* min = FindMin(r);
            min->right = RemoveMin(r);
            min->left = q;
            return Balance(min);
        }
        else
            n->right = Remove(n->right,k);

        return Balance(n);
    }

    Node<T>* FindIndex(Node<T>* n, const int& searched_index, int parent_index)
    {
        if (n == nullptr)
            return nullptr;

        int current_index = abs(parent_index -1 - NodesCount(n->left));
        if(current_index == searched_index)
            return n;
        else if(current_index > searched_index)
            return FindIndex(n->left, searched_index, current_index);
        else
            return FindIndex(n->right, searched_index, -current_index);
    }
};


bool Meq(const int& f, const int& s)
{
    return f >= s;
}


bool Leq(const int& f, const int& s)
{
    return f <= s;
}


int main()
{
    AvlTree<int> avlt(Leq);
    int ccounter;
    int command;
    int key;

    cin >> ccounter;
    for(int i = 0; i < ccounter; i++)
    {
        cin >> command >> key;

        switch(command)
        {
            case 1:
            avlt.Add(key);
            cout << avlt.FindKeyIndex(key) << endl;
            break;

            case 2:
            avlt.Delete(key);
            break;

            default:
            break;
        }
    }

    return 0;
}






























