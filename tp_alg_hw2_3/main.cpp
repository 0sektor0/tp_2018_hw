#include <iostream>
#include "assert.h"
#include <vector>
#include <stack>
#include "cmath"

using namespace std;



template<class K, class P>
struct TreapNode
{
    K key;
    P priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode(const K& key, const P& priority)
    {
        this->key = key;
        this->priority = priority;
        left = nullptr;
        right = nullptr;
    }
};


template<class K, class P>
class Treap
{
public:
    Treap(bool (*kcomp)(const K&, const K&), bool (*pcomp)(const P&, const P&))
    {
        this->kcomp = kcomp;
        this->pcomp = pcomp;
        root = nullptr;
    }

    void Insert(const K& key, const P& prirority)
    {
        TreapNode<K,P>* node = new TreapNode<K,P>(key, prirority);

        if(root != nullptr)
        {
            TreapNode<K,P>* cnode = root;
            TreapNode<K,P>* pnode = nullptr;

            while(pcomp(cnode->priority, node->priority))
            {
                if (!kcomp(node->key, cnode->key))
                {
                    if (cnode->left == nullptr)
                    {
                        cnode->left = node;
                        return;
                    }
                    else
                    {
                        pnode = cnode;
                        cnode = cnode->left;
                    }
                }
                else
                {
                    if (cnode->right == nullptr)
                    {
                        cnode->right = node;
                        return;
                    }
                    else
                    {
                        pnode = cnode;
                        cnode = cnode->right;
                    }
                }
            }

            Split(cnode, node->key, node->left, node->right);
            if(pnode != nullptr)
            {
                if(kcomp(node->key, pnode->key))
                    pnode->right = node;
                else
                    pnode->left = node;
            }
            else
                root = node;
        }
        else
            root = node;
    }

    int Depth()
    {
        if(root == nullptr)
            return 0;

        int max_depth = 0;
        stack<TreapNode<K,P>*> nodes_st;
        stack<int> depth_st;

        nodes_st.push(root);
        depth_st.push(max_depth);

        while(!nodes_st.empty())
        {
            TreapNode<K,P>* cnode = nodes_st.top();
            nodes_st.pop();

            int node_depth = depth_st.top();
            depth_st.pop();
            node_depth++;

            if(node_depth > max_depth)
                max_depth = node_depth;

            if(cnode->left != nullptr)
            {
                nodes_st.push(cnode->left);
                depth_st.push(node_depth);
            }
            if(cnode->right != nullptr)
            {
                nodes_st.push(cnode->right);
                depth_st.push(node_depth);
            }
        }

        return max_depth;
    }

    ~Treap()
    {
        if(root != nullptr)
        {
            stack<TreapNode<K,P>*> dnodes;
            TreapNode<K,P>* cnode;

            dnodes.push(root);
            while(!dnodes.empty())
            {
                cnode = dnodes.top();
                dnodes.pop();

                if(cnode->left)
                    dnodes.push(cnode->left);

                if(cnode->right)
                    dnodes.push(cnode->right);

                delete cnode;
            }
        }
    }


private:
    TreapNode<K,P>* root;
    bool (*pcomp)(const P&, const P&);
    bool (*kcomp)(const K&, const K&);

    void Split(TreapNode<K,P>* root, const K& key, TreapNode<K,P>*& left, TreapNode<K,P>*& right)
    {
        if(root == nullptr)
            left = right = nullptr;
        else if (!kcomp(key, root->key))
            Split(root->left, key, left, root->left),  right = root;
        else
            Split(root->right, key, root->right, right),  left = root;
    }

    TreapNode<K,P>* Merge(TreapNode<K,P>* left, TreapNode<K,P>* right)
    {
        if(left == nullptr || right == nullptr)
            return left == nullptr ? right : left;
        if(pcomp(left->priority >= right->priority))
        {
            left->right = Merge(left->right, right);
            return left;
        }
        else
        {
            right->left = Merge(left, right->left);
            return right;
        }
    }
};



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
        if (root != nullptr)
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

    int Depth()
    {
        if(root == nullptr)
            return 0;

        int max_depth = 0;
        stack<BstNode<T>*> nodes_st;
        stack<int> depth_st;

        nodes_st.push(root);
        depth_st.push(max_depth);

        while(!nodes_st.empty())
        {
            BstNode<T>* cnode = nodes_st.top();
            nodes_st.pop();

            int node_depth = depth_st.top();
            depth_st.pop();
            node_depth++;

            if(node_depth > max_depth)
                max_depth = node_depth;

            if(cnode->left != nullptr)
            {
                nodes_st.push(cnode->left);
                depth_st.push(node_depth);
            }
            if(cnode->right != nullptr)
            {
                nodes_st.push(cnode->right);
                depth_st.push(node_depth);
            }
        }

        return max_depth;
    }

private:
    bool (*meq) (const T&, const T&);
    BstNode<T>* root;
    int len;
};


bool meq(const int& f1, const int& f2)
{
    return f1 > f2;
}



int main()
{
    Treap<int,int> treap(meq, meq);
    Bst<int> bst(meq);
    int counter;
    int priority;
    int key;

    cin >> counter;
    for(int i = 0; i < counter; i++)
    {
        cin >> key >> priority;
        treap.Insert(key, priority);
        bst.Add(key);
    }

    cout << abs(treap.Depth()-bst.Depth());
    return 0;
}
































