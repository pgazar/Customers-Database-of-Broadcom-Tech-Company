/*
// Binary tree abstract base class
// Written By: A. Student
// Changed By: Joel J Morancy
// IDE: Visual Studio
Description:
    Binary Tree base class will take in Customer objects and sort them based on the compare function is passed to the tree.
    Derived classes must implement insert, remove, and search
*/
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include <iostream>
#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;		// ptr to root node
    int count;							// number of nodes in tree

public:
    // "admin" functions
    BinaryTree() { rootPtr = 0; count = 0; }
    BinaryTree(const BinaryTree<ItemType>& tree) { rootPtr = 0; count = 0; }
    virtual ~BinaryTree() { destroyTree(rootPtr); }

    // common functions for all binary trees
    bool isEmpty() const { return count == 0; }
    int getCount() const { return count; }
    void clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; }
    void inOrder(void visit(ItemType&)) const { _inorder(visit, rootPtr); }
    void printTree(void visit(ItemType&, int)) const { _printTree(visit, rootPtr, 1); }

    // abstract functions to be implemented by derived class
    virtual bool insert(const ItemType& item, int compare(ItemType, ItemType)) = 0;
    virtual BinaryNode<ItemType>* remove(const ItemType& item, int compare(ItemType, ItemType)) = 0;
    virtual bool search(void visit(ItemType& item), const ItemType& target, int& num, int compare(ItemType, ItemType)) const = 0;

private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);

    // internal traverse
    void _inorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
    void _printTree(void visit(ItemType&, int), BinaryNode<ItemType>* nodePtr, int level) const;

};

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr) // != NULL
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        //cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
        delete nodePtr;
    }
}


//Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

//Prints tree as an indented list
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void visit(ItemType&, int), BinaryNode<ItemType>* nodePtr, int level) const
{
    if (nodePtr) // != NULL
    {
        ItemType item = nodePtr->getItem();
        visit(item, level);
        _printTree(visit, nodePtr->getRightPtr(), level + 1);
        _printTree(visit, nodePtr->getLeftPtr(), level + 1);
    }
}


#endif

