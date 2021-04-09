#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Node
{
private:
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    T value;
public:
    Node(T value)
    {
        this->value = value;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    Node<T>* getLeft()
    {
        return left;
    }

    Node<T>* getRight()
    {
        return right;
    }

    Node<T>* getParent()
    {
        return parent;
    }

    void setLeft(Node<T>* left)
    {
        this->left = left;
    }

    void setParent(Node<T>* parent)
    {
        this->parent = parent;
    }

    void setRight(Node<T>* right)
    {
        this->right = right;
    }

    T getValue()
    {
        return value;
    }
    bool isLeaf()
    {
        return (left == NULL && right == NULL);
    }

    ~Node()
    {
        value = 0;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};
