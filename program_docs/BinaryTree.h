// Binary tree class

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include <string>
#include "HashTable.h"
#include <vector>
using std::vector;
template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
    HashTable<ItemType>  hash;
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
   virtual ~BinaryTree() { destroyTree(rootPtr); }
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int getCount() const {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
   void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
   void printTree(void visit(ItemType &, int)) const{_printTree(visit, rootPtr, 1);}
    void printLeaf(void visit(ItemType &)) const  {_printLeaf(visit, rootPtr);}
    void printAll(vector<ItemType>& display) const { _printAll(rootPtr, display); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType &newData) = 0;


private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _printTree(void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const;
    void _printAll(BinaryNode<ItemType>* nodePtr, vector<ItemType>& display) const;
}; 

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if(nodePtr) // != NULL
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        //cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
        delete nodePtr;
    }
}  


//Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
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
void BinaryTree<ItemType>::_printTree(void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const
{
    if (nodePtr)
    {
         ItemType item = nodePtr->getItem();
         visit(item, level);
        // Process right child first
          _printTree(visit, nodePtr->getRightPtr(), level+1);
          // Process left child
          _printTree(visit, nodePtr->getLeftPtr(), level+1);
    }
}


//Print all nodes
template<class ItemType>
void BinaryTree<ItemType>::_printAll(BinaryNode<ItemType>* nodePtr, vector<ItemType>& display) const
{
    /* Write your code here */
    //vector<ItemType> display;
    if (nodePtr)
    {
        _printAll(nodePtr->getLeftPtr(), display);
        
        ItemType item = nodePtr->getItem();
        display.push_back(item);
        _printAll(nodePtr->getRightPtr(), display);
        
    
    }
}

#endif

