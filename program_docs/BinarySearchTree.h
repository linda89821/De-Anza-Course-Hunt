// Binary Search Tree ADT

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include <vector>
using std::vector;

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
public:
    // insert a node at the correct location
    bool insert(const ItemType &item);
    // remove a node if found
    bool remove(const ItemType& anEntry, ItemType &returnedItem);
    // find a target node
    bool search(const ItemType &anEntry, vector<ItemType> &returnedItem) const;

    
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
    
    // internal insert node: delete newNode in nodePtr subtree
    BinaryNode<ItemType>* _delete(BinaryNode<ItemType>* nodePtr, const ItemType target) const;
    
	// search for target node
	void _search(BinaryNode<ItemType>* nodePtr, const ItemType& target, vector<ItemType>& matches) const;

	BinaryNode<ItemType>* _searchDelete(BinaryNode<ItemType>* nodePtr, const ItemType& target) const;
    
   // find the smallest node
   BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr) const;

    
};


///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}  

//Wrapper for _search
// - it calls the private _search function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller 
//   via the output parameter, and returns true, otherwise it returns false.
template<class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType& anEntry, vector<ItemType>& returnedItem) const
{
	vector<ItemType> matches;
    _search(this->rootPtr, anEntry, matches);
    if(!matches.empty())
    {
        returnedItem = matches;
        return true;
    }
    return false;
}

//Wrapper for _delete
// - it calls the private _delete function that returns a Node pointer or NULL
// - if found, it deletes data from that node and sends it back to the caller
//   via the output parameter, and returns true, otherwise it returns false.
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& anEntry, ItemType & returnedItem)
{
    BinaryNode<ItemType>* temp = _searchDelete(this->rootPtr, anEntry);
    if(temp)
    {
        returnedItem = temp->getItem();
        this->rootPtr = _delete(this->rootPtr, anEntry);
        return true;
    }
    return false;
}

//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr)
{
    BinaryNode<ItemType>* pWalk = nodePtr;
    
    if(!nodePtr) // == NULL
    {
        nodePtr = newNodePtr;
    }
    else
    {
        if (pWalk->getItem() > newNodePtr->getItem())
            pWalk->setLeftPtr(_insert(pWalk->getLeftPtr(), newNodePtr));
        else
            pWalk->setRightPtr(_insert(pWalk->getRightPtr(), newNodePtr));

    }

    return nodePtr;
}

//Implementation for the search operation
// - return NULL if target not found, otherwise
// - returns a pointer to the node that matched the target
template<class ItemType>
void BinarySearchTree<ItemType>::_search(BinaryNode<ItemType>* nodePtr, const ItemType &target, vector<ItemType> &matches) const
{
    BinaryNode<ItemType>* pWalk = nodePtr;
    
    if(pWalk)
    {
        if(pWalk->getItem() > target)
            _search(nodePtr->getLeftPtr(), target, matches);
        else if(pWalk->getItem() < target)
			_search(pWalk->getRightPtr(), target, matches);
        else{
			matches.push_back(pWalk->getItem());
            _search(pWalk->getRightPtr(), target, matches);
        }
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_searchDelete(BinaryNode<ItemType>* nodePtr,	const ItemType &target) const
{
	BinaryNode<ItemType>* found = nullptr;

	BinaryNode<ItemType>* pWalk = nodePtr;

	if (pWalk)
	{
		if (pWalk->getItem() > target)
			found = _searchDelete(nodePtr->getLeftPtr(), target);
		else if (pWalk->getItem() < target)
			found = _searchDelete(pWalk->getRightPtr(), target);
		else {
			if (pWalk->getItem() == target)
				found = pWalk;
			else
				found =_searchDelete(pWalk->getRightPtr(), target);
		}
	}
	return found;
}

/* Given a binary search tree and a key, this function deletes the key
and returns the new root */
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_delete(BinaryNode<ItemType>* root, const ItemType target) const
{
    // base case
    if (root == nullptr)
        return root;
  
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (target < root->getItem())
        root->setLeftPtr(_delete(root->getLeftPtr(), target));
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (target > root->getItem())
        root->setRightPtr(_delete(root->getRightPtr(), target));
  
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
		if (target == root->getItem()) {
			// node with no child
			if (root->getLeftPtr() == nullptr && root->getRightPtr() == nullptr)
			{
				delete root;
				root = nullptr;
			}
			// node with one child
			else if (root->getRightPtr() == nullptr)
			{
				BinaryNode<ItemType>* temp = root;
				root = root->getLeftPtr();
				delete temp;
			}
			else if (root->getLeftPtr() == nullptr)
			{
				BinaryNode<ItemType>* temp = root;
				root = root->getRightPtr();
				delete temp;
			}
			// node with two childs
			else
			{
				// node with two children: Get the inorder successor (smallest
				// in the left subtree)
				BinaryNode<ItemType>* temp = _findSmallest(root->getRightPtr());

				// Copy the inorder successor's content to this node
				root->setItem(temp->getItem());

				// Delete the inorder successor
				root->setRightPtr(_delete(root->getRightPtr(), temp->getItem()));
			}
		}
		else
			root->setRightPtr(_delete(root->getRightPtr(), target));
    }
    return root;

}

//Implementation to find the smallest: recursive
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType>* nodePtr) const
{
    ItemType smallest;
    if (nodePtr == nullptr)
      return nullptr;

    if(nodePtr->getLeftPtr() == nullptr)
    {
        smallest = nodePtr->getItem();
        return nodePtr;
    }

    return _findSmallest(nodePtr->getLeftPtr());
 }

#endif
