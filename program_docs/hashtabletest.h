// Name: Masato Ishizuka
//  IDE: Xcode

/*A hash table is a data structure that stores data in units of pairs of keys and corresponding values, and when a key is specified, the corresponding value can be obtained at high speed.*/

#ifndef HashTable_h
#define HashTable_h

#include "HashNode.h"
//#include "LinkedList.h"

template<class ItemType>
class HashTable
{
private:
    HashNode<ItemType>* hashAry;
    int hashSize;
    int count;

public:
    HashTable() { count = 0; hashSize = 53; hashAry = new HashNode<ItemType>[hashSize]; }
    HashTable(int n) { count = 0; hashSize = n; hashAry = new HashNode<ItemType>[hashSize]; }
    ~HashTable() { delete[] hashAry; }

    int getCount() const { return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const { return 100.0 * count / hashSize; }
    bool isEmpty() const { return count == 0; }
    bool isFull()  const { return count == hashSize; }

    bool insert(const ItemType& itemIn, int h(const ItemType& key, int size));
    bool remove(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size));
    int  search(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size));

    int totalCollisions() const;
    int longestLinkedList() const;
    void handleCollision(const ItemType& itemIn, int h(const ItemType& key, int size));
    void populateStack(Stack<ItemType>& stack);


};

/*~*~*~*
   Insert an item into the hash table
   It does not reject duplicates
*~**/
template<class ItemType>
bool HashTable<ItemType>::insert(const ItemType& itemIn, int h(const ItemType& key, int size))
{
    if (count == hashSize)
        return false;

    int i = h(itemIn, hashSize);
    int nCol = hashAry[i].getNoCollisions();

    if (hashAry[i].getOccupied() == 0) {
        hashAry[i].setItem(itemIn);
        hashAry[i].setOccupied(1);
        count++;
    }
    else {
        handleCollision(itemIn, h);
        nCol++;
    }

    hashAry[i].setNoCollisions(nCol);

    return true;
}

/*~*~*~*
   Removes the item with the matching key from the hash table
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record
*~**/
template<class ItemType>
bool HashTable<ItemType>::remove(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size))
{
    int index = h(key, hashSize);
    int nCol = 0;

    while (nCol < hashSize && hashAry[index].getOccupied() != 0) {
        if (hashAry[index].getItem() == key) {
            HashNode<ItemType> temp(itemOut, -1, 0);
            itemOut = hashAry[index].getItem();
            hashAry[index] = temp;
            count--;
            return true;
        }
        else {
            hashAry[index].deleteNode(key);
            count--;
        }

        nCol++;
        index = (index + 1) % hashSize;
    }

    return false;
}

/*~*~*~*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns the number of collisions for this key
   if not found, returns -1
*~**/
template<class ItemType>
int HashTable<ItemType>::search(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size))
{
    int index = h(key, hashSize);
    int nCol = 0;

    while (nCol < hashSize && hashAry[index].getOccupied() != 0) {
        if (hashAry[index].getItem() == key) {
            itemOut = hashAry[index].getItem();
            return hashAry[index].getNoCollisions();
        }
        else {
            hashAry[index].searchNode(key, itemOut);
        }

        nCol++;
        index = (index + 1) % hashSize;
    }

    return -1;
}

template<class ItemType>
int HashTable<ItemType>::totalCollisions() const
{
    int totalCol = 0;
    for (int i = 0; i < hashSize; i++) {
        if (hashAry[i].getOccupied() == 1)
            totalCol += hashAry[i].getNoCollisions();
    }

    return totalCol;
}
template<class ItemType>
int HashTable<ItemType>::longestLinkedList() const
{
    int longest = 0;
    int numCol = 0;
    for (int i = 0; i < hashSize; i++) {
        numCol = hashAry[i].getNoCollisions();
        if (numCol > longest) {
            longest = numCol;
        }
    }

    return longest;
}

template<class ItemType>
void HashTable<ItemType>::handleCollision(const ItemType& itemIn, int h(const ItemType& key, int size))
{
    int i = h(itemIn, hashSize);
    hashAry[i].insertNode(itemIn);
    int numCol = hashAry[i].getNoCollisions();
    numCol++;
    hashAry[i].setNoCollisions(numCol);

}

//**************************************************
// The populateStack function iterates through hashtable
// passing a stack to each hashnode to populate
//**************************************************
template<typename ItemType>
void HashTable<ItemType>::populateStack(Stack<ItemType>& stack)
{
    for (int i = 0; (i < hashSize); i++)
    {
        // in the for block meaning:
        // we have not reached the end of the hash table
        if (hashAry[i].getOccupied() == 1) {
            hashAry[i].populateStack(stack);
        }


    }
}

#endif /* HashTable_h */
