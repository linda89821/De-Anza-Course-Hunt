/*~*~*
   Stack template
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
      StackNode *next;  // Pointer to next node
    };

    StackNode *top;     // Pointer to the stack top
    int length;

public:
    // Constructor
    Stack()
    { top = nullptr; length = 0;}
    // Destructor
    ~Stack();
    
    void push(T);
    void pop(T &);
    T peek()
    { return top->value;}
    bool isEmpty();
    T getLength()
    {return length;}
};


/*~*~*
 Destructor
*~**/
template <class T>
Stack<T>::~Stack()
{
    StackNode *nodePtr, *nextNode;
    
    // set the nodePtr to the top of the stack.
    nodePtr = top;
    
    while (nodePtr != nullptr)
    {
        nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

/*~*~*
  Member function push inserts the argument onto
  the stack.
*~**/

template <class T>
void Stack<T>::push(T item)
{
    StackNode *newNode = nullptr;
    
    //dynamically allocate and store the number
    newNode = new StackNode;
    newNode->value = item;
    
    if(!isEmpty())
    {
        newNode->next = top;
        top = newNode;
        length++;
    }
    else
    {
        top = newNode;
        newNode->next = nullptr;
        length++;
    }
    
}

/*~*~*
  Member function pop deletes the value at the top
  of the stack and returns it.
  Assume stack is not empty.
*~**/
template <class T>
void Stack<T>::pop(T &item)
{
    StackNode *temp = nullptr;
    
    item = top->value;
    temp = top->next;
    delete top;
    top = temp;
    
    length--;
    
}

/*~*~*
  Member function isEmpty
*~**/

template <class T>
bool Stack<T>::isEmpty()
{
    bool status;
    
    if(!top)
        status = true;
    else
        status = false;
    
    return status;
}


#endif
