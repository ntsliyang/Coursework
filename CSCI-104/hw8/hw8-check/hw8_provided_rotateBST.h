#ifndef ROTATE_BST_H
#define ROTATE_BST_H

#include "bst.h"

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{
public:
	bool sameKeys(const rotateBST& t2);
	void transform(rotateBST& t2) const;
protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);
};

template <typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST<Key, Value>& t2)
{
	return false;
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST<Key, Value>& t2) const
{

}

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r)
{

}

template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r)
{

}

#endif