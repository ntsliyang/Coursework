#ifndef CACHELRU_H
#define CACHELRU_H

#include "splayTree.h"
#include <stdexcept>

template<typename Key, typename Value>
class cacheLRU : public SplayTree<Key, Value> 
{
	public:
	cacheLRU(int capacity);
	~cacheLRU();
	void put(const std::pair<const Key, Value>& keyValuePair);
	std::pair<const Key, Value> get(const Key& key);

	private:
	int size;
	int capacity;
};

template<typename Key, typename Value>
cacheLRU<Key, Value>::cacheLRU(int capacity) 
{
	this->capacity = capacity; // set the capacity to the given number 
	size = 0; // initialize the current size
}

template<typename Key, typename Value>
cacheLRU<Key, Value>::~cacheLRU() 
{

}

template<typename Key, typename Value>
void cacheLRU<Key, Value>::put(const std::pair<const Key, Value>& keyValuePair)
{
	Node<Key, Value>* node = BinarySearchTree<Key, Value>::internalFind(keyValuePair.first);
	if (node == NULL) { // if such node does not exist
		SplayTree<Key, Value>::insert(keyValuePair);
		size++;
	}
	else {
 		SplayTree<Key, Value>::splay(node);
	}

	// insert the keyValuePair into the cache
	if (size > capacity) {
		SplayTree<Key, Value>::deleteMinLeaf(); 
      size--;
 	// remove the leaf with the minimum value key
    }
 }

template<typename Key, typename Value>
std::pair<const Key, Value> cacheLRU<Key, Value>::get(const Key& key) 
{
	typename SplayTree<Key, Value>::iterator i = SplayTree<Key, Value>::find(key);
	// find a node with the specified key in the tree
	if (i == this->end()) {
		throw std::logic_error("Key not found");
	} // throw a logic_error exception if the value is not found 
	else {
		return *(i);
	} // return the key/value pair
}


#endif
