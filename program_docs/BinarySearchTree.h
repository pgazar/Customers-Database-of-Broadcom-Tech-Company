/*
// Binary Search Tree ADT
// Written By: A. Student
// Changed By: Joel J Morancy
// IDE: Visual Studio
   Description:
   Binary Search Tree will take in Customer objects and sort them based on the compare function is passed to the tree.
   Synonyms will be inserted in an arbitrary order, and can be all be found and printed.
   A Customers first transaction can be found in logarithmic time
*/

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <iostream>
#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
public:
    // insert a node at the correct location
    bool insert(const ItemType& item, int compare(ItemType, ItemType));
    // remove a node if found
    BinaryNode<ItemType>* remove(const ItemType& item, int compare(ItemType, ItemType));
    // find a target node
    bool search(void visit(ItemType& item), const ItemType& target, int& num, int compare(ItemType, ItemType)) const;

private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, int compare(ItemType, ItemType));

    // search for target node
    BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType& target, void visit(ItemType& item), int& num, int compare(ItemType, ItemType)) const;

    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* _removeNode(BinaryNode<ItemType>* targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& successor);

    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool& success, int compare(ItemType, ItemType));


};


///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
//always returns true
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType& newEntry, int compare(ItemType, ItemType))
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr, compare);
    return true;
}

//Wrapper for _search
/* - it calls the private _search function that returns a Node pointer or NULL
// - if found, true is returned
// - if not found, false is returned 
*/
template<class ItemType>
bool BinarySearchTree<ItemType>::search(void visit(ItemType& item), const ItemType& anEntry, int& num, int compare(ItemType, ItemType)) const
{
    num = 0;
    BinaryNode<ItemType>* temp = nullptr;
    temp = _search(this->rootPtr, anEntry, visit, num, compare);
    if (temp)
    {
        return true;
    }
    return false;
}


//Wrapper for _remove
/* - it calls the private _remove function that returns a Node pointer or NULL
// - if found, it delinks that node from the tree
// - output parameter is left unchanged*/
template<typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::remove(const ItemType& item, int compare(ItemType, ItemType)) {
    bool succ = false;
    BinaryNode<ItemType>* removedNode = _remove(this->rootPtr, item, succ, compare);

    if (succ)
    {
        this->count--;
    }
    return removedNode; // Node not found
}



//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr, int compare(ItemType, ItemType))
{
    BinaryNode<ItemType>* pWalk = nodePtr;

    if (!nodePtr) // == NULL
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }

    ItemType itemA = pWalk->getItem();
    ItemType newItem = newNodePtr->getItem();
    int comparison = compare(newItem, itemA);

    if (comparison == -1)
        nodePtr->setLeftPtr(_insert(pWalk->getLeftPtr(), newNodePtr, compare));
    else
        nodePtr->setRightPtr(_insert(pWalk->getRightPtr(), newNodePtr, compare));
    return nodePtr;
}

//Implementation for the search operation
// - return NULL if target not found, otherwise
// - returns a pointer to the FIRST node that matched the target
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_search(BinaryNode<ItemType>* nodePtr, const ItemType& target, void visit(ItemType& item), int& num, int compare(ItemType, ItemType)) const
{
    BinaryNode<ItemType>* found = NULL;

    if (!nodePtr) {
        return found;
    }

    ItemType itemA = nodePtr->getItem();
    int comparison = compare(target, itemA);

    if (comparison == -1)
        found = _search(nodePtr->getLeftPtr(), target, visit, num, compare);
    else if (comparison == 1)
        found = _search(nodePtr->getRightPtr(), target, visit, num, compare);
    else
    {
        num++;
        found = nodePtr;
        visit(itemA);

        //handle duplicates
        //print all synonyms in right sub tree
        _search(nodePtr->getRightPtr(), target, visit, num, compare);
        //print all duplicates in left sub tree
        _search(nodePtr->getLeftPtr(), target, visit, num, compare);
    }

    return found;
}

//Helper function for _remove (for nodes with 1 child)
// delete target node from tree, called by internal remove node
// nodeptr must not be null
template<typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeNode(BinaryNode<ItemType>* targetNodePtr)
{
    // return the target node's child
    if (!targetNodePtr->getLeftPtr() && !targetNodePtr->getRightPtr())
    {
        return 0;
    }
    else if (!targetNodePtr->getRightPtr())
    {
        return targetNodePtr->getLeftPtr();
    }
    else
    {
        return targetNodePtr->getRightPtr();
    }
}

//Helper function for _remove (for nodes with 2 children)
// remove the leftmost node in the left subtree of nodePtr
// coppies data to output parameter
// nodePtr must not be null
// returns that node, must be delinked by calling function
template<typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& successor)
{
    // traversal pointers
    BinaryNode<ItemType>* par = 0;
    BinaryNode<ItemType>* cur = nodePtr;

    //traverse left until leaf reached
    while (cur->getLeftPtr())
    {
        par = cur;
        cur = cur->getLeftPtr();
    }
    //copy leafs data, then set parents left pointer to cur's right subtree
    successor = cur->getItem();
    if (par)
    {
        par->setLeftPtr(_removeNode(cur));
    }
    return cur;
}

//Implementation for the remove operation
// internal remove node: locate and de-link target node under nodePtr subtree
// - returns a pointer to the BinaryNode removed.
// - returns a NULL pointer if target node not found
template<typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool& success, int compare(ItemType, ItemType)) {
    BinaryNode<ItemType>* par = 0;
    BinaryNode<ItemType>* cur = nodePtr;
    success = false;

    while (cur)
    {
        //compare our node with target
        ItemType currentItem = cur->getItem();
        int comparison = compare(target, currentItem);
        //check if root is target node
        if (comparison == 0)
        {
            //handle duplicates, traverse to the correct cusno
            while (!(currentItem == target))
            {
                cur = cur->getRightPtr();
                currentItem = cur->getItem();
            }
            if (!cur->getLeftPtr() && !cur->getRightPtr())
            {
                //case 1: remove leaf
                if (!par)
                {
                    this->rootPtr = _removeNode(cur);
                }
                else if (par->getLeftPtr() == cur)
                {
                    //return target nodes subtree
                    par->setLeftPtr(_removeNode(cur));
                }
                else
                {
                    //return target nodes subtree
                    par->setRightPtr(_removeNode(cur));
                }
                cur->setLeftPtr(0);
                cur->setRightPtr(0);
                success = true;
                return cur;
            }
            else if (!cur->getRightPtr())
            {
                //case 2: remove node with only left child
                if (!par)
                {
                    this->rootPtr = _removeNode(cur);
                }
                else if (par->getLeftPtr() == cur)
                {
                    //return target nodes subtree
                    par->setLeftPtr(_removeNode(cur));
                }
                else
                {
                    //return target nodes subtree
                    par->setRightPtr(_removeNode(cur));
                }
                cur->setLeftPtr(0);
                cur->setRightPtr(0);
                success = true;
                return cur;

            }
            else if (!cur->getLeftPtr())
            {
                //case 3: remove node with only right child
                if (!par)
                {
                    this->rootPtr = _removeNode(cur);
                }
                else if (par->getLeftPtr() == cur)
                {
                    //return target nodes subtree
                    par->setLeftPtr(_removeNode(cur));
                }
                else
                {
                    //return target nodes subtree
                    par->setRightPtr(_removeNode(cur));
                }
                cur->setLeftPtr(0);
                cur->setRightPtr(0);
                success = true;
                return cur;
            }
            else
            {
                //case 4: remove node with two children
                ItemType succData;


                // remove the leftmost node in the left subtree of nodePtr
                BinaryNode<ItemType>* removedNode = _removeLeftmostNode(cur->getRightPtr(), succData);

                //set successor data to cur's
                removedNode->setItem(cur->getItem());
                cur->setItem(succData);

                //cur is now successor, set cur equal to removed node (node to delete)
                cur = removedNode;
                cur->setLeftPtr(0);
                cur->setRightPtr(0);
                success = true;
                return cur;
            }
        }
        else if (comparison == 1)
        {
            //search right subtree
            par = cur;
            cur = cur->getRightPtr();
        }
        else
        {
            //search left subtree
            par = cur;
            cur = cur->getLeftPtr();
        }
    }

    //not deleted, not found
    cur = NULL;
    return cur;
}


#endif
