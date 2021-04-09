#include "BST_Node.cpp"
#define INVALID -1000000000

template <typename T>
class BST
{
private:
    Node<T>* root;
public:
    BST()
    {
        root = NULL;
    }

    BST(T rootValue)
    {
        this->root = new Node<T>(rootValue);
    }

    void insertItem(T item)
    {
        Node<T>* elem = new Node<T>(item);
        if(isEmpty())
        {
            this->root = elem;
            return;
        }

        Node<T>* cur = root;
        while(cur != NULL)
        {
            if(elem->getValue() < cur->getValue())
            {
                if(cur->getLeft() != NULL)cur = cur->getLeft();
                else{
                    cur->setLeft(elem);
                    elem->setParent(cur);
                    return;
                }
            }
            else
            {
                if(cur->getRight() != NULL)cur = cur->getRight();
                else{
                    cur->setRight(elem);
                    elem->setParent(cur);
                    return;
                }
            }
        }

    }

    void searchItem(T value)
    {

        Node<T>* cur = find(this->root, value);
        if(cur == NULL) cout<<value<<" has not been found. "<<endl;
        else cout<<value<<" has been found. "<<endl;

    }


    T getInOrderSuccessor(T value)
    {
        Node<T>* succesor = getNextMax(find(this->root, value));
        if(succesor == NULL)return INVALID;
        else return succesor->getValue();
    }



    T getInOrderPredecessor(T value)
    {
        Node<T>* predecessor = getPrevMax(find(this->root, value));
        if(predecessor == NULL)return INVALID;
        else return predecessor->getValue();
    }


    void deleteItem(T value)
    {
        Node<T>* cur = find(this->root, value);
        if(cur == NULL)return;


        if(cur->isLeaf())
        {
            detach(cur);
            if(cur == this->root) this->root = NULL;
            delete cur;
            return;
        }

        Node<T>* parent = cur->getParent(); //Assuming function caller doesn't want to delete root
        Node<T>* rep;                       //replacement node

        if(cur->getRight() == NULL)
        {
            rep = cur->getLeft();

            detach(cur);
            detach(rep);

            attach(parent, rep);
            delete cur;
        }

        else if(cur->getLeft() == NULL)
        {
            rep = cur->getRight();

            detach(cur);
            detach(rep);

            attach(parent, rep);
            delete cur;
        }

        else
        {
            rep = getNextMax(cur);           //replacement will be the next max item
            Node<T>* right = cur->getRight();
            Node<T>* left = cur->getLeft();
            if(rep == right)
            {
                //isolating cur node
                detach(cur);
                detach(left);
                detach(rep);

                //connecting the replacement
                attach(parent, rep);
                attach(rep, left);

                delete cur;
                return;
            }
            else
            {
                Node<T>* rep_parent = rep->getParent();
                Node<T>* rep_right = rep->getRight();

                detach(rep);
                detach(rep_right);

                attach(rep_parent, rep_right);

                detach(cur);
                detach(left);
                detach(right);

                attach(rep, right);
                attach(rep, left);
                attach(parent, rep);

                delete cur;
                return;
            }

        }

    }


    T getMaxItem()
    {
        Node<T>* max = getMaxItemNode(this->root);
        if(max == NULL)return -1;
        return max->getValue();
    }


    Node<T>* getMaxItemNode(Node<T>* root)
    {
        if(isEmpty())return NULL;
        Node<T>* cur  = root;
        while(cur->getRight() != NULL)cur = cur->getRight();
        return cur;
    }


    T getMinItem()
    {
        Node<T>* min = getMinItemNode(this->root);
        if(min == NULL)return -1;
        return min->getValue();
    }


    Node<T>* getMinItemNode(Node<T>* root)
    {
        if(isEmpty())return NULL;
        Node<T>* cur  = root;
        while(cur->getLeft() != NULL)cur = cur->getLeft();
        return cur;
    }

    int getHeight()
    {
        if(this->root->isLeaf())return 0;
        if(isEmpty())return -1;
        return getHeight(this->root);
    }

    int getHeight(Node<T>* root)
    {
        if(root == NULL || root->isLeaf())return 0;
        else return max(getHeight(root->getLeft()), getHeight(root->getRight())) + 1;
    }


    int getSize()
    {
        if(isEmpty())return 0;
        return getSize(this->root);
    }

    int getSize(Node<T>* root)
    {
        if(root == NULL)return 0;
        if(root->isLeaf())return 1;
        return getSize(root->getLeft()) + getSize(root->getRight()) + 1;
    }

    int getItemDepth(T item)
    {
        int depth = 0;
        Node<T>* cur = root;
        while(cur != NULL)
        {
            if(cur->getValue() == item)return depth;
            else if(item < cur->getValue())cur = cur->getLeft();
            else cur = cur->getRight();
            depth++;
        }
        return -1;
    }

    void printInOrder()
    {
        if(isEmpty())return;
        cout<<"InOrder : ";
        printInOrder(this->root);
        cout<<endl;
    }

    void printInOrder(Node<T>* root)
    {
        if(root == NULL)return;
        printInOrder(root->getLeft());
        cout<<root->getValue()<<" ";
        printInOrder(root->getRight());
    }

    void printPreOrder()
    {
        if(isEmpty())return;
        cout<<"PreOrder : ";
        printPreOrder(this->root);
        cout<<endl;
    }

    void printPreOrder(Node<T>* root)
    {
        if(root == NULL)return;
        cout<<root->getValue()<<" ";
        printPreOrder(root->getLeft());
        printPreOrder(root->getRight());
    }
    void printPostOrder()
    {
        if(isEmpty())return;
        cout<<"PostOrder : ";
        printPostOrder(this->root);
        cout<<endl;
    }

    void printPostOrder(Node<T>* root)
    {
        if(root == NULL)return;
        printPostOrder(root->getLeft());
        printPostOrder(root->getRight());
        cout<<root->getValue()<<" ";
    }


    Node<T>* find(Node<T>* root, T key)
    {
        if(root == NULL || root->getValue() == key) return root;
        if(key < root->getValue())return find(root->getLeft(), key);
        else return find(root->getRight(), key);

    }


    bool isEmpty()
    {
        return root == NULL;
    }

    //cut the Node det from its parent but does not delete the node
    void detach(Node<T>* det)
    {
        if(det == NULL)return;
        if(det->getParent() == NULL)
        {
            cout<<"the node has no parent "<<endl;
            return;
        }
        if(det == det->getParent()->getLeft())det->getParent()->setLeft(NULL);
        else det->getParent()->setRight(NULL);

        det->setParent(NULL);
    }

    //attach the child node to the parent node
    void attach(Node<T>* parent, Node<T>* child)
    {
        if(child == NULL)return;
        if(parent->getLeft() != NULL && parent->getRight()!=NULL)return;
        if(child->getValue() < parent->getValue())
        {
            if(parent->getLeft() != NULL)return;
            parent->setLeft(child);
        }

        if(child->getValue() > parent->getValue())
        {
            if(parent->getRight() != NULL)return;
            parent->setRight(child);
        }

        child->setParent(parent);
    }

    Node<T>* getNextMax(Node<T>* elem)
    {
        Node<T>* cur = elem;
        if(cur == NULL)return NULL;

        if(cur->getRight() != NULL) return getMinItemNode(cur->getRight()); // returns the min item of the right subtree


        else
        {
            Node<T>* prev = cur;
            cur = prev->getParent();

            //finds the parent node whose left subtree's max item is elem
            while(cur != NULL && cur->getRight() == prev)
            {
                prev = cur;
                cur = prev->getParent();
            }

            return cur;
        }
    }

    //finds previous maximum item before elem node and returns the node
    Node<T>* getPrevMax(Node<T>*elem)
    {
        Node<T>* cur = elem;
        if(cur == NULL)return cur;

        if(cur->getLeft() != NULL) return getMaxItemNode(cur->getLeft());

        else
        {
            Node<T>* prev = cur;
            cur = prev->getParent();

            //finds the parent node whose right subtree's max item is elem
            while(cur != NULL && cur->getLeft() == prev)
            {
                prev = cur;
                cur = prev->getParent();
            }
            return cur;
        }
    }

    //Recursively deletes the whole subtree rooted at cur
    void remove(Node<T>* cur)
    {
        if(cur->getLeft()!=NULL)remove(cur->getLeft());
        if(cur->getRight()!=NULL)remove(cur->getRight());
        delete cur;
    }


    ~BST()
    {
        if(!isEmpty())remove(root);
    }

};
