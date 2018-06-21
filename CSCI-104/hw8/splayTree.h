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
	private:
	Node<Key, Value>* getLargestNode() const;
	Node<Key, Value> *maxValueNode(Node<Key, Value> *node);
	Node<Key, Value> *minValueNode(Node<Key, Value> *node);
	void deleteMinLeafHelper(Node<Key, Value>* node);
	void deleteMaxLeafHelper(Node<Key, Value>* node);
	Node<Key, Value> *findLastVisited(const Key& key);
};

template <typename Key, typename Value>
SplayTree<Key, Value>::SplayTree()
{

}

template <typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	BinarySearchTree<Key, Value>::insert(keyValuePair); // use insert function in bst
	Node<Key, Value>* node = findLastVisited(keyValuePair.first);
	if (node != NULL) splay(node);
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{
	Node<Key, Value>* node = findLastVisited(key);
	if (node != NULL && node->getKey() == key) {
		if (node->getLeft() != NULL && node->getRight() != NULL)  {
			Node<Key, Value>* pred = maxValueNode(node->getLeft());
				if (pred->getParent() == node) {
					BinarySearchTree<Key, Value>::remove(key);
					splay(pred);
				} // splay the predecessor if the predecessor's parent is 
				// the deleted node 
				else {
					Node<Key, Value>* p = pred->getParent();
					BinarySearchTree<Key, Value>::remove(key);
					splay(p);
				} // splay the predecessor's parent if the predecessor's 
				// parent is not the deleted node 
		} // if both nodes' children are present, then we splay the 
		// children to the root 

		else {
			Node<Key, Value>* p = node->getParent();
			BinarySearchTree<Key, Value>::remove(key);
			splay(p);
		} // In other cases, we would splay the parent of the deleted node
	}
	else if (node != NULL && node->getKey() != key) {
		splay(node);
	} // if we did not find the deleted node, we would splay the lastly 
	// visited node
}

template <typename Key, typename Value>
Node<Key, Value> *SplayTree<Key, Value>::findLastVisited(const Key& key) {
	Node<Key, Value> *node = this->mRoot;
	while (node != NULL)
	{
		if (node->getKey() == key) {
			return node;
		}
		else if (node->getKey() > key) {
			if (node->getLeft()) {
				node = node->getLeft();
			}
			else {
				return node;
			}
		}
		else if (node->getKey() < key) {
			if (node->getRight()) {
				node = node->getRight();
			}
			else {
				return node;
			}
		}
	} // find the lastly visited node 
	return NULL; // if the root is nullptr, then we return nullptr
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key)
{
	Node<Key, Value>* node = findLastVisited(key);
	if (node == NULL) {
		return this->end();
	} 
	else if (node->getKey() == key) {
		splay(node);
		typename SplayTree<Key, Value>::iterator i(node);
		return i;
	} // if we find the deleted node, then we return the iterator of the deleted node 
	else {
		splay(node);
		return this->end();
	}  // if we don't find the node, we return the end iterator 
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin()
{
	Node<Key, Value>* node = BinarySearchTree<Key, Value>::getSmallestNode();
	if (node != NULL) {
		splay(node);
		return BinarySearchTree<Key, Value>::find(node->getKey());
	}
	return this->end();
}

template <typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::getLargestNode() const {
	Node<Key, Value> *temp = this->mRoot;
	while (temp != NULL && temp->getRight())
	{
		temp = temp->getRight();
	}
	return temp;
}


template <typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::minValueNode(Node<Key, Value> *node) {
	Node<Key, Value> *temp = node;
	while (temp != NULL && temp->getLeft())
	{
		temp = temp->getLeft();
	}
	return temp; // return the leftmost node
}

template <typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::maxValueNode(Node<Key, Value> *node) {
	Node<Key, Value> *temp = node;
	while (temp != NULL && temp->getRight())
	{
		temp = temp->getRight();
	}
	return temp; // return the rightmost node
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax()
{
	Node<Key, Value>* node = getLargestNode();
	if (node != NULL) {
		splay(node);
		return BinarySearchTree<Key, Value>::find(node->getKey());
	}
	return this->end();
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeafHelper(Node<Key, Value>* node) {
	if (node->getLeft() == NULL && node->getRight() == NULL) {
		remove(node->getKey());
	}
	else if (node->getLeft() != NULL) {
		deleteMinLeafHelper(minValueNode(node));
	}
	else if (node->getRight() != NULL) {
		node = node->getRight();
		deleteMinLeafHelper(node);
	}
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeafHelper(Node<Key, Value>* node) {
	if (node->getLeft() == NULL && node->getRight() == NULL) {
		remove(node->getKey());
	}
	else if (node->getLeft() == NULL && node->getRight() != NULL) {
		deleteMaxLeafHelper(maxValueNode(node));
	}
	else if (node->getLeft() != NULL && node->getRight() == NULL) {
		node = node->getLeft();
		deleteMaxLeafHelper(node);
	}
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf()
{
	Node<Key, Value>* node = minValueNode(this->mRoot);
	if (node != NULL) deleteMinLeafHelper(node); 
	// find the nodes of all leaves, and delete the smallest of them
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf()
{
	Node<Key, Value>* node = maxValueNode(this->mRoot);
	if (node != NULL) deleteMaxLeafHelper(node);
	// find the nodes of all leaves, and delete the smallest of them
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r)
{
	if (r == NULL) return;
	if (r == this->mRoot) return; // which means that it doesn't have parent
	else { // r must have a parent 
			while (r != this->mRoot) {
				// Node<Key, Value>* p = r->getParent();
				if (r->getParent() == NULL) {
					break;
				} // parent equals to NULL, r would be the root
				else if (r->getParent() == this->mRoot) { // if r's r->getParent()arent is the root of tree (zig)
					if (r->getParent()->getLeft() == r) {
						this->rightRotate(r->getParent());  // right rotate the parent 
					}
					else if (r->getParent()->getRight() == r) {
						this->leftRotate(r->getParent()); // left rotate the parent
					}
				}
				else if (r->getParent()->getParent()) { // p has a parent (r has a great-grandparent)
					// Node<Key, Value>* pp = p->getParent();
					if (r->getParent()->getLeft() == r && r->getParent()->getParent()->getLeft() == r->getParent()) { // zig-zig 
						this->rightRotate(r->getParent()->getParent());
						this->rightRotate(r->getParent());
					}
					else if (r->getParent()->getRight() == r && r->getParent()->getParent()->getLeft() == r->getParent()) { // zig-zag
						this->leftRotate(r->getParent());
						this->rightRotate(r->getParent());
					}
					else if (r->getParent()->getRight() == r && r->getParent()->getParent()->getRight() == r->getParent()) { // zag-zag
						this->leftRotate(r->getParent()->getParent());
						this->leftRotate(r->getParent());
					}
					else if (r->getParent()->getLeft() == r && r->getParent()->getParent()->getRight() == r->getParent()) { // zag-zig 
						this->rightRotate(r->getParent());
						this->leftRotate(r->getParent());
					}
				}
			}
	}
}

#endif
