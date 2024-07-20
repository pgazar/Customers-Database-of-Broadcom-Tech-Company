/*~*~*
 Stack template
 Created by Pegah Zargarian
 *~*/

#ifndef STACK_ADT
#define STACK_ADT

template <class T>
class Stack
{
private:
    // Structure for the stack nodes
    struct StackNode
    {
        T value;          // Value in the node
        StackNode* next;  // Pointer to next node
    };

    StackNode* top;     // Pointer to the stack top
    int length;

public:
    Stack() {                          // Constructor
        top = NULL;
        length = 0;
    }
    ~Stack() {                           //Destructor
        if (!isEmpty()) {
            while (!isEmpty()) {
                pop();
            }
            std::cout << "\n";
        }
    }

    // Stack operations:
    bool push(T);
    T pop();

    T peek() {
        return top->value;
    }
    bool isEmpty()
    {
        if (top) {
            return false;
        }
        else {
            return true;
        }
    }
    int getLength() {
        return length;
    }
};

/*~*~*
 Member function push inserts the argument onto
 the stack.
 *~**/
template <class T>
bool Stack<T>::push(T item)
{
    StackNode* newNode; // Pointer to a new node

    // Allocate a new node and store num there.
    newNode = new StackNode;
    if (!newNode)
        return false;
    newNode->value = item;

    // Update links and counter
    newNode->next = top;
    top = newNode;
    length++;

    return true;
}


/*~*~*
 Member function pop deletes the value at the top
 of the stack and returns it.
 Assume stack is not empty.
 *~**/
template<class T>
T Stack<T>::pop() {
    T head;
    if (!isEmpty()) {
        // Allocate a new node.
        StackNode* tempNode = new StackNode;

        head = top->value;
        tempNode = top;
        top = top->next;
        delete tempNode;
        --length;

    }
    return head;
}


#endif
