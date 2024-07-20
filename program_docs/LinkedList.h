// Name: Masato Ishizuka
//  IDE: Xcode

#ifndef LinkedList_h
#define LinkedList_h

#include "Customer.h"
#include "StackADT.h"

class LinkedList
{
private:
    struct Node
    {
        Customer cus;
        Node* next;
    };

    Node* head;
    int length;

public:
    LinkedList();   // constructor
    ~LinkedList();  // destructor

    // Linked list operations
    int getLength() const { return length; }
    void insertNode(Customer);
    bool deleteNode(string);
    bool searchList(string, Customer&) const;
    void populateStack(Stack<Customer> &stack);
};

//**************************************************
// Constructor
// This function allocates and initializes a sentinel node
//      A sentinel (or dummy) node is an extra node added before the first data record.
//      This convention simplifies and accelerates some list-manipulation algorithms,
//      by making sure that all links can be safely dereferenced and that every list
//      (even one that contains no data elements) always has a "first" node.
//**************************************************
LinkedList::LinkedList()
{
    head = new Node; // head points to the sentinel node
    head->next = NULL;
    length = 0;
}

//**************************************************
// The insertNode function inserts a new node in a
// sorted linked list
//**************************************************
void LinkedList::insertNode(Customer dataIn)
{
    Node* newNode;  // A new node
    Node* pCur;     // To traverse the list
    Node* pPre;     // The previous node

    // Allocate a new node and store num there.
    newNode = new Node;
    newNode->cus = dataIn;

    // Initialize pointers
    pPre = head;
    pCur = head->next;

    // Find location: skip all nodes whose code is less than dataIn's code
    while (pCur && newNode->cus.getCusNum() > pCur->cus.getCusNum())
    {
        pPre = pCur;
        pCur = pCur->next;
    }

    // Insert the new node between pPre and pCur
    pPre->next = newNode;
    newNode->next = pCur;

    // Update the counter
    length++;
}

//**************************************************
// The deleteNode function searches for a node
// in a sorted linked list; if found, the node is
// deleted from the list and from memory.
//**************************************************
bool LinkedList::deleteNode(string target)
{
    Node* pCur;       // To traverse the list
    Node* pPre;       // To point to the previous node
    bool deleted = false;

    // Initialize pointers
    pPre = head;
    pCur = head->next;

    // Find node containing the target: Skip all nodes whose gpa is less than the target
    while (pCur != NULL && pCur->cus.getCusNum() < target)
    {
        pPre = pCur;
        pCur = pCur->next;
    }

    // If found, delte the node
    if (pCur && pCur->cus.getCusNum() == target)
    {
        pPre->next = pCur->next;
        delete pCur;
        deleted = true;
        length--;
    }
    return deleted;
}




//**************************************************
// Destructor
// This function deletes every node in the list.
//**************************************************
LinkedList::~LinkedList()
{
    Node* pCur;     // To traverse the list
    Node* pNext;    // To hold the address of the next node

    // Position nodePtr: skip the head of the list
    pCur = head->next;
    // While pCur is not at the end of the list...
    while (pCur != NULL)
    {
        // Save a pointer to the next node.
        pNext = pCur->next;

        // Delete the current node.
        delete pCur;

        // Position pCur at the next node.
        pCur = pNext;
    }

    delete head; // delete the sentinel node
}

//**************************************************
// The searchList function looks for a target college
// in the sorted linked list: if found, returns true
// and copies the data in that node to the output parameter
//**************************************************
bool LinkedList::searchList(string target, Customer& dataOut) const
{
    bool found = false; // assume target not found
    Node* pCur;         // To move through the list

    pCur = head->next;

    while (pCur) {
        if (pCur->cus.getCusNum() == target) {
            found = true;
            dataOut = pCur->cus;
            break;
        }
        pCur = pCur->next;
    }

    return found;
}


//**************************************************
// The populateStack function iterates through all nodes
// in the linked list
// and copies the data in that node to the output parameter
//**************************************************
void LinkedList::populateStack(Stack<Customer>& stack)
{
    bool found = false; // assume target not found
    Node* pCur;         // To move through the list

    //set current pointer to first node
    pCur = head->next;

    //if there is a node, will push each to stack
    while (pCur)
    {
        stack.push(pCur->cus);
        pCur = pCur->next;
    }
}

#endif /* LinkedList_h */
