#include "BinarySearchTree.cpp"

int main()
{
    BST<int> tree;

    cout<<" 1. INSERT ITEM "<<endl;
    cout<<" 2. SEARCH ITEM "<<endl;
    cout<<" 3. GET IN ORDER SUCCESSOR ITEM "<<endl;
    cout<<" 4. GET IN ORDER PREDECESSOR ITEM "<<endl;
    cout<<" 5. DELETE ITEM "<<endl;
    cout<<" 6. GET ITEM DEPTH "<<endl;
    cout<<" 7. GET MAX ITEM "<<endl;
    cout<<" 8. GET MIN ITEM "<<endl;
    cout<<" 9. GET HEIGHT OF THE TREE "<<endl;
    cout<<" 10.PRINT IN ORDER TRAVERSAL "<<endl;
    cout<<" 11.PRINT PRE ORDER TRAVERSAL "<<endl;
    cout<<" 12.PRINT POST ORDER TRAVERSAL "<<endl;
    cout<<" 13.GET SIZE OF THE TREE "<<endl;
    cout<<" ENTER '0' TO EXIT "<<endl;

    while(1)
    {
        int cmd;
        cin>>cmd;
        if(cmd == 0)break;

        if(cmd == 1)
        {
            int c;
            cin>>c;
            tree.insertItem(c);
        }

        else if(cmd == 2)
        {
            int c;
            cin>>c;
            tree.searchItem(c);
        }

        else if(cmd == 3)
        {
            int c;
            cin>>c;
            cout<<"Inorder successor of "<<c<<" is "<< tree.getInOrderSuccessor(c)<<endl;
        }

        else if(cmd == 4)
        {
            int c;
            cin>>c;
            cout<<"Inorder predecessor of "<<c<<" is "<<tree.getInOrderPredecessor(c)<<endl;
        }

        else if(cmd == 5)
        {
            int c;
            cin>>c;
            tree.deleteItem(c);
            cout<<c<< " is deleted" <<endl;
        }

        else if(cmd == 6)
        {
            int c;
            cin>>c;
            cout<<"The depth of "<<c<<" is "<<tree.getItemDepth(c)<<endl;
        }

        else if(cmd == 7) cout<<"MAX Item : "<<tree.getMaxItem()<<endl;

        else if(cmd == 8) cout<<"Min item : "<<tree.getMinItem()<<endl;

        else if(cmd == 9) cout<<"Height : "<<tree.getHeight()<<endl;

        else if(cmd == 10)tree.printInOrder();

        else if(cmd == 11)tree.printPreOrder();

        else if(cmd == 12)tree.printPostOrder();

        else if(cmd == 13)cout<<"Size : "<<tree.getSize()<<endl;

    }
}
