#ifndef ROTATEBST_H
#define ROTATEBST_H

#include "bst.h"
#include <vector>

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{
  public:
	bool sameKeys(const rotateBST &t2) const;
	void transform(rotateBST &t2) const;

  protected:
	void leftRotate(Node<Key, Value> *r);
	void rightRotate(Node<Key, Value> *r);

  private:
	void leftRotate(Node<Key, Value> *r, bool heightUpdate);
	void rightRotate(Node<Key, Value> *r, bool heightUpdate);
	void traversal(Node<Key, Value> *root, std::vector<Key> &s) const;
	void recRotate(Node<Key, Value> *r2, Node<Key, Value> *r1, rotateBST<Key, Value> &t2);
	void updateHeight(Node<Key, Value> *node);
};

template <typename Key, typename Value>
void rotateBST<Key, Value>::updateHeight(Node<Key, Value> *node)
{
	if (node->getLeft() == NULL && node->getRight() == NULL)
	{
		node->setHeight(1);
	}
	else if (node->getLeft() == NULL && node->getRight() != NULL)
	{
		node->setHeight(node->getRight()->getHeight() + 1);
	}
	else if (node->getRight() == NULL && node->getLeft() != NULL)
	{
		node->setHeight(node->getLeft()->getHeight() + 1);
	}
	else {
		node->setHeight(std::max(node->getLeft()->getHeight(), node->getRight()->getHeight()) + 1);
	}
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::traversal(Node<Key, Value> *root, std::vector<Key> &s) const
{
	if (root == NULL) return;
	else {
		traversal(root->getLeft(), s);
		s.push_back(root->getKey());
		traversal(root->getRight(), s);
	}
}

template <typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST<Key, Value> &t2) const
{
	std::vector<Key> s1;
	std::vector<Key> s2;
	Node<Key, Value> *r1 = this->mRoot;
	Node<Key, Value> *r2 = t2.mRoot;
	traversal(r1, s1);
	traversal(r2, s2);
	return (s1 == s2);
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::recRotate(Node<Key, Value> *r2, Node<Key, Value> *r1, rotateBST<Key, Value> &t2) {
	if (r2 == NULL || r1 == NULL) return;
		Node<Key, Value>* lchild = r2->getLeft();
		Node<Key, Value>* rchild = r2->getRight();
		if (lchild != NULL && r1 != NULL) {
			if (r1->getLeft() != NULL) {
				while (lchild->getKey() != r1->getLeft()->getKey()) {
					t2.rightRotate(lchild, false);
					lchild = lchild->getParent();
				}
				lchild->setHeight(r1->getLeft()->getHeight());
			}
		}
		
		if (rchild != NULL && r1 != NULL) {
			if (r1->getRight() != NULL) {
				while (rchild->getKey() != r1->getRight()->getKey()) {
					t2.leftRotate(rchild, false);
					rchild = rchild->getParent();
				}
				rchild->setHeight(r1->getRight()->getHeight());
			}
		}
		if (lchild != NULL) recRotate(lchild, r1->getLeft(), t2);
		if (rchild != NULL) recRotate(rchild, r1->getRight(), t2);
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST<Key, Value> &t2) const
{
	if (!(this->sameKeys(t2)))
		return;

	if (t2.mRoot == NULL) return;
	while (t2.mRoot->getLeft())
	{
		t2.rightRotate(t2.mRoot, false);
	} // Perform right rotations on the root node of t2 until it has no left child.
	Node<Key, Value> *r2 = t2.mRoot->getRight();
	while (r2 != NULL) 
	{
		while (r2->getLeft() != NULL)
		{
			t2.rightRotate(r2, false);
			r2 = r2->getParent();
		} // Recursively move to the right child and repeat the above operation.
		r2 = r2->getRight();
	}
	while (t2.mRoot->getKey() != this->mRoot->getKey())
	{
		t2.leftRotate(t2.mRoot, false);
	} // perform left rotations on the root node of t2, 
	// until the root of t2 is the same as the root of this
	t2.mRoot->setHeight(this->mRoot->getHeight());

	t2.recRotate(t2.mRoot, this->mRoot, t2);
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value> *r, bool heightUpdate) {
		if (r == NULL) return;
	if (r->getRight() == NULL)
		return; // no right child, then do nothing
	Node<Key, Value> *rright = r->getRight();
	Node<Key, Value> *rrightleft = rright->getLeft();
	if (r->getParent())
	{
		Node<Key, Value> *p = r->getParent();
		if (p->getRight() == r)
		{
			p->setRight(rright);
		}
		else if (p->getLeft() == r)
		{ 
			p->setLeft(rright);
		}
		rright->setParent(p);
	}
	rright->setLeft(r);
	r->setParent(rright);
	r->setRight(rrightleft);
	if (rrightleft)
		rrightleft->setParent(r);
	if (r == this->mRoot) {
		this->mRoot = rright;
		rright->setParent(NULL);
	}
	if (heightUpdate) {
	while (r)
	{
		this->updateHeight(r);
		r = r->getParent();
	} // update the height of relevant node
	}
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value> *r)
{
	if (r == NULL) return;
	if (r->getRight() == NULL)
		return; // no right child, then do nothing
	Node<Key, Value> *rright = r->getRight();
	Node<Key, Value> *rrightleft = rright->getLeft();
	if (r->getParent())
	{
		Node<Key, Value> *p = r->getParent();
		if (p->getRight() == r)
		{
			p->setRight(rright);
		}
		else if (p->getLeft() == r)
		{ 
			p->setLeft(rright);
		}
		rright->setParent(p);
	}
	rright->setLeft(r);
	r->setParent(rright);
	r->setRight(rrightleft);
	if (rrightleft)
		rrightleft->setParent(r);
	if (r == this->mRoot) {
		this->mRoot = rright;
		rright->setParent(NULL);
	}
	while (r)
	{
		this->updateHeight(r);
		r = r->getParent();
	} // update the height of relevant node
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value> *r, bool heightUpdate) {
	if (r == NULL) return;
	if (r->getLeft() == NULL)
		return; // no left child, then do nothing
	Node<Key, Value> *rleft = r->getLeft();
	Node<Key, Value> *rleftright = rleft->getRight();
	if (r->getParent())
	{
		Node<Key, Value> *p = r->getParent();
		if (p->getRight() == r)
		{
			p->setRight(rleft);
		}
		else if (p->getLeft() == r)
		{ 
			p->setLeft(rleft);
		}
		rleft->setParent(p);
	}
	rleft->setRight(r);
	r->setParent(rleft);
	r->setLeft(rleftright);
	if (rleftright)
		rleftright->setParent(r);
	if (r == this->mRoot) {
		this->mRoot = rleft;
		rleft->setParent(NULL);
	}
	if (heightUpdate) {
	while (r)
	{
		this->updateHeight(r);
		r = r->getParent();
	} // update the height of relevant node
	}
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value> *r)
{
	if (r == NULL) return;
	if (r->getLeft() == NULL)
		return; // no left child, then do nothing
	Node<Key, Value> *rleft = r->getLeft();
	Node<Key, Value> *rleftright = rleft->getRight();
	if (r->getParent())
	{
		Node<Key, Value> *p = r->getParent();
		if (p->getRight() == r)
		{
			p->setRight(rleft);
		}
		else if (p->getLeft() == r)
		{ 
			p->setLeft(rleft);
		}
		rleft->setParent(p);
	}
	rleft->setRight(r);
	r->setParent(rleft);
	r->setLeft(rleftright);
	if (rleftright)
		rleftright->setParent(r);
	if (r == this->mRoot) {
		this->mRoot = rleft;
		rleft->setParent(NULL);
	}
	while (r)
	{
		this->updateHeight(r);
		r = r->getParent();
	} // update the height of relevant node
}

#endif
