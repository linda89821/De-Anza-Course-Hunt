// Specification file for the Hash class
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"

template<class ItemType>
class HashTable
{
private:
	HashNode<ItemType>* hashAry;
	int hashSize;
	int count;
	int totalCollision;
	int longestCollisions;
	int findNextPrime(int n);

public:
	HashTable() { count = 0; hashSize = 53; hashAry = new HashNode<ItemType>[hashSize]; totalCollision = 0; longestCollisions = 0; }
	HashTable(int n);
	~HashTable() { delete[] hashAry; }

	int getCount() const { return count; }
	int getSize() const { return hashSize; }
	double getLoadFactor() const { return 100.0 * count / hashSize; }
	int getLongestCollisions() const { return longestCollisions; }
	int getTotalCollision() const { return totalCollision; }
	bool isEmpty() const { return count == 0; }
	bool isFull()  const { return count == hashSize; }

	bool insert(const ItemType& itemIn, int h(const ItemType& key, int size));
	bool remove(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size));
	int  search(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size)) const;
	void reHash(int n, int h(const ItemType& key, int size));
};

/*~*~*~*
   Hash table 
*~**/
template<class ItemType>
HashTable<ItemType>::HashTable(int n) { 
	count = 0;
	totalCollision = 0; 
	longestCollisions = 0;
	hashSize = findNextPrime(n);	
	hashAry = new HashNode<ItemType>[hashSize]; 
}

/*~*~*~*
   finding the next prime number
*~**/
template<class ItemType>
int HashTable<ItemType>::findNextPrime(int n){
	bool found = false;
	n += 1;
	while (!found) {
		found = true;
		for (int i = 3; i * i <= n; i += 2) {
			if (n % i == 0) {
				n += 2;
				found = false;
				break;
			}
		}
	}
	return n;
}

/*~*~*~*
   Insert an item into the hash table
   It does not reject duplicates
*~**/
template<class ItemType>
bool HashTable<ItemType>::insert(const ItemType& itemIn, int h(const ItemType& key, int size))
{
	if (count == hashSize)
		return false;
	int position = h(itemIn, hashSize);
	int noCollision = 0;
	ItemType empty;
	while (hashAry[position].getItem() != empty) {
		totalCollision++;
		noCollision++;
		position += (noCollision % 2 ? noCollision : -noCollision);
		position %= hashSize;
	}
	longestCollisions = noCollision > longestCollisions ? noCollision : longestCollisions;
	hashAry[position].setItem(itemIn);
	hashAry[position].setNoCollisions(noCollision);
	hashAry[position].setOccupied(1);
	count++;
	if (count > hashSize * 3 / 4) {
		reHash(count*2, h);
	}
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
	int position = h(key, hashSize);
	int found = search(itemOut, key, h);
	if (found != -1) {
		position += found;
		position %= hashSize;
		hashAry[position].setItem(*(new ItemType));
		count -= 1;
		return true;
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
int HashTable<ItemType>::search(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size)) const
{
	int position = h(key, hashSize);
	int noCol = 0;
	while (hashAry[position].getOccupied() && key != hashAry[position].getItem()) {
		noCol++;
		position += (noCol % 2 ? noCol : -noCol);
		position %= hashSize;
		if (noCol > hashSize)
			return -1;
	}
	if (!hashAry[position].getOccupied())
		return -1;
	itemOut = hashAry[position].getItem();
	return noCol;
}

/*~*~*~*
   Re-hasing:
   When load factor is 75%, allocate
   another hash table
*~**/

template<class ItemType>
void HashTable<ItemType>::reHash(int n, int h(const ItemType& key, int size)) {
	HashNode<ItemType>* oldAry = hashAry;
	int oldHashSize = hashSize;
	count = 0;
	totalCollision = 0;
	longestCollisions = 0;
	hashSize = findNextPrime(n);
	hashAry = new HashNode<ItemType>[hashSize];
	ItemType empty;
	for (int i = 0; i < oldHashSize; i++) {
		if (oldAry[i].getItem() != empty) {
			insert(oldAry[i].getItem(), h);
		}
	}
	delete[] oldAry;
}
#endif // HASHTABLE_H_
