// Name: Masato Ishizuka
//  IDE: Xcode

#ifndef HashNode_h
#define HashNode_h

#include "LinkedList.h"

template<class ItemType>
class HashNode
{
private:
    ItemType item;
    int occupied;
    int noCollisions;
    LinkedList nodeList;

public:
    // constructors
    HashNode() { occupied = 0; noCollisions = 0; }
    HashNode(ItemType anItem) { item = anItem; occupied = 1; noCollisions = 0; }
    HashNode(ItemType anItem, int ocp, int nCol) { item = anItem; occupied = ocp; noCollisions = nCol; }
    // setters
    void setItem(const ItemType& anItem) { item = anItem; }
    void setOccupied(int ocp) { occupied = ocp; }
    void setNoCollisions(int nCol) { noCollisions = nCol; }

    // getters
    ItemType getItem() const { return item; }
    int getOccupied() const { return occupied; }
    int getNoCollisions() const { return noCollisions; }

    void insertNode(ItemType);
    void deleteNode(string);
    void searchNode(string, ItemType&) const;
    void populateStack(Stack<ItemType>& stack);
};

template<class ItemType>
void HashNode<ItemType>::insertNode(ItemType ItemIn)
{
    nodeList.insertNode(ItemIn);
}

template<class ItemType>
void HashNode<ItemType>::deleteNode(string target)
{
    nodeList.deleteNode(target);
}

template<class ItemType>
void HashNode<ItemType>::searchNode(string target, ItemType &dataOut) const
{
    nodeList.searchList(target, dataOut);
}

//**************************************************
// The populateStack function passes a stack to the linked list
// and calls populateStack member function of the linked list
// take care to only pass Stack<Customer>   <-- TODO: Fix
//**************************************************
template<typename ItemType>
void HashNode<ItemType>::populateStack(Stack<ItemType>& stack)
{
    nodeList.populateStack(stack);
}

#endif /* HashNode_h */