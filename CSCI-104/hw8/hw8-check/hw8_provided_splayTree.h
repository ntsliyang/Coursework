#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "rotateBST.h"

template <typename Key, typename Value>
class SplayTree : public rotateBST<Key, Value>
{
public:
	SplayTree();
	void insert(const std::pair<const Key, Value>& keyValuePair);
	void remove(const Key& key);
	typename SplayTree<Key, Value>::iterator find(const Key& key);
	typename SplayTree<Key, Value>::iterator findMin();
	typename SplayTree<Key, Value>::iterator findMax();
	void deleteMinLeaf();
	void deleteMaxLeaf();
protected:
	void splay(Node<Key, Value> *r);
};

template <typename Key, typename Value>
SplayTree<Key, Value>::SplayTree()
{

}

template <typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{

}

template <typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{

}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key)
{
	return this->begin();
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin()
{
	return this->begin();
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax()
{
	return this->begin();
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf()
{

}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf()
{

}

template <typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r)
{

}

#endif