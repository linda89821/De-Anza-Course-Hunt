#ifndef _BINARY_NODE_DATA
#define _BINARY_NODE_DATA
#include "BinaryNode.h"

template<class ItemType>

class BinaryNodeData: public BinaryNode<ItemType>
{
private:
    ItemType key;       // key: secondary key
    ItemType value[];     // value: array of primary key
    

public:
    // constructors
    BinaryNode<ItemType>* BinaryNodeData()
    BinaryNode(const ItemType & anItem)    {item = anItem; leftPtr = 0; rightPtr = 0;}
    BinaryNode(const ItemType & anItem,
               BinaryNode<ItemType>* left,
               BinaryNode<ItemType>* right) {item = anItem; leftPtr = left; rightPtr = right;}
    // setters
    void setItem(const ItemType & anItem) {item = anItem;}
    void setLeftPtr(BinaryNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) {rightPtr = right;}
    
    // getters
    ItemType getItem() const     {return item;}
    BinaryNode<ItemType>* getLeftPtr() const  {return leftPtr;}
    BinaryNode<ItemType>* getRightPtr() const {return rightPtr;}

    // other functions
    bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
    
};

#endif
