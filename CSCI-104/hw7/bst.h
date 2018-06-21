#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
  public:
	Node(const Key &key, const Value &value, Node<Key, Value> *parent);
	virtual ~Node();

	const std::pair<const Key, Value> &getItem() const;
	std::pair<const Key, Value> &getItem();
	const Key &getKey() const;
	const Value &getValue() const;
	Value &getValue();

	virtual Node<Key, Value> *getParent() const;
	virtual Node<Key, Value> *getLeft() const;
	virtual Node<Key, Value> *getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value> *parent);
	void setLeft(Node<Key, Value> *left);
	void setRight(Node<Key, Value> *right);
	void setValue(const Value &value);
	void setHeight(int height);

  protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value> *mParent;
	Node<Key, Value> *mLeft;
	Node<Key, Value> *mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template <typename Key, typename Value>
Node<Key, Value>::Node(const Key &key, const Value &value, Node<Key, Value> *parent)
	: mItem(key, value), mParent(parent), mLeft(NULL), mRight(NULL), mHeight(1)
{
}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/

template <typename Key, typename Value>
Node<Key, Value>::~Node()
{
}

/**
* A const getter for the item.
*/
template <typename Key, typename Value>
const std::pair<const Key, Value> &Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item. 
*/
template <typename Key, typename Value>
std::pair<const Key, Value> &Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template <typename Key, typename Value>
const Key &Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template <typename Key, typename Value>
const Value &Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the value.
*/
template <typename Key, typename Value>
Value &Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A const getter for the height.
*/
template <typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template <typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value> *parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template <typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value> *left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template <typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value> *right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template <typename Key, typename Value>
void Node<Key, Value>::setValue(const Value &value)
{
	mItem.second = value;
}

/**
* A setter for the height of a node.
*/
template <typename Key, typename Value>
void Node<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
  public:
	BinarySearchTree();													  //TODO
	virtual ~BinarySearchTree();										  //TODO
	int height();														  //TODO
	bool isBalanced();													  //TODO
	virtual void insert(const std::pair<const Key, Value> &keyValuePair); //TODO
	virtual void remove(const Key &key);								  //TODO
	void clear();														  //TODO
	void print() const;

  public:
	/**
		* An internal iterator class for traversing the contents of the BST.
		*/
	class iterator
	{
	  public:
		iterator(Node<Key, Value> *ptr);
		iterator();

		std::pair<const Key, Value> &operator*();
		std::pair<const Key, Value> *operator->();

		bool operator==(const iterator &rhs) const;
		bool operator!=(const iterator &rhs) const;
		iterator &operator=(const iterator &rhs);

		iterator &operator++();

	  protected:
		Node<Key, Value> *mCurrent;
	};

  public:
	iterator begin();
	iterator end();
	iterator find(const Key &key) const;

  protected:
	Node<Key, Value> *internalFind(const Key &key) const; //TODO
	Node<Key, Value> *getSmallestNode() const;			  //TODO
	void printRoot(Node<Key, Value> *root) const;

  protected:
	Node<Key, Value> *mRoot;

  private:
	int heighthelper(Node<Key, Value> *node);
	bool balancedhelper(Node<Key, Value> *node);
	void updateHeight(Node<Key, Value> *node);
	Node<Key, Value> *maxValueNode(Node<Key, Value> *node);
	void clearhelper(Node<Key, Value> *node);
};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key, Value> *ptr)
	: mCurrent(ptr)
{
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{
}

/**
* Provides access to the item.
*/
template <typename Key, typename Value>
std::pair<const Key, Value> &BinarySearchTree<Key, Value>::iterator::operator*()
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template <typename Key, typename Value>
std::pair<const Key, Value> *BinarySearchTree<Key, Value>::iterator::operator->()
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator &rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator &rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator &rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator++()
{
	if (mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while (mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if (mCurrent->getRight() == NULL)
	{
		Node<Key, Value> *parent = mCurrent->getParent();
		while (parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	// TODO
	mRoot = NULL;
	//	mRoot->setParent(NULL);
	//	mRoot->setLeft(NULL);
	//	mRoot->setRight(NULL);
	//	mRoot->setHeight(0);
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	// TODO
	clear();
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key &key) const
{
	Node<Key, Value> *curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

template <typename Key, typename Value>
int BinarySearchTree<Key, Value>::heighthelper(Node<Key, Value> *node)
{
	if (node == NULL)
		return 0;
	else
	{
		// node->setHeight(1 + std::max(heighthelper(node->getLeft()), heighthelper(node->getRight())));
		return 1 + std::max(heighthelper(node->getLeft()), heighthelper(node->getRight()));
	}
}

/**
* An method to return the height of the BST.
*/
template <typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	// TODO
	if (!mRoot) return 0;
	return mRoot->getHeight();
}
	
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balancedhelper(Node<Key, Value> *node)
{
	if (node == NULL)
		return true;
	// if bst is empty, then it must be balanced
	int lheight = heighthelper(node->getLeft());
	int rheight = heighthelper(node->getRight());
	if (abs(lheight - rheight) <= 1 && balancedhelper(node->getLeft()) && balancedhelper(node->getRight()))
		return true;
	// left subtree and right subtree are balanced
	// difference in height between left subtree and right subtree is no more than 1
	return false;
}
/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	// TODO
	Node<Key, Value> *node = mRoot;
	return balancedhelper(node);
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
	// TODO
	// Node<Key, Value>* node = mRoot;
	Node<Key, Value> *temp = NULL;
	// // create a new pair temp
	Node<Key, Value> *node = mRoot;
	// // create a traversing node that is initially the root of the tree
	if (mRoot == NULL)
	{
		temp =  new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		mRoot = temp;
	}
	// if it is an empty tree, insert the new node as the root of tree
	else
	{ // if it is not an empty tree, traverse from the top to bottom
		while (node != NULL)
		{
			if (node->getKey() < keyValuePair.first)
			{ // if the value inserted is larger than the current node's key,
				// traverse to the right subtree
				if (node->getRight() == NULL)
				{ // if a node's right node is empty, insert here
					temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
					node->setRight(temp);
					temp->setParent(node);
					break;
				}
				node = node->getRight();
			}
			else if (node->getKey() > keyValuePair.first)
			{ // if the value inserted is smaller than the current node's key,
				// traverse to the left subtree
				if (node->getLeft() == NULL)
				{ // if a node's left node is empty, insert here
					temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);	
					node->setLeft(temp);
					temp->setParent(node);
					break;
				}
				node = node->getLeft();
			}
			else
				return;
		}
	}
	while (temp)
	{
		updateHeight(temp);
		temp = temp->getParent();
	}
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::updateHeight(Node<Key, Value> *node)
{
	// if (node == NULL) {
	// 	node->setHeight(0);
	// }
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
Node<Key, Value> *BinarySearchTree<Key, Value>::maxValueNode(Node<Key, Value> *node)
{
	Node<Key, Value> *temp = node;
	while (temp->getRight())
	{
		temp = temp->getRight();
	}
	return temp;
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key &key)
{
	// TODO
	//Node<Key, Value> *node = new Node<Key, Value>;
	Node<Key, Value> *del = this->internalFind(key);
	// use internalFind to find such node
	if (!del)
		return; // if such node does not exist, just return
	if (del->getLeft() == NULL && del->getRight() == NULL)
	{
		// if this node is a leafnode
		if (del == mRoot)
		{
			// if this node is the root of bst
			delete mRoot;
			mRoot = NULL;
		}
		else if (del->getParent() != NULL)
		{
			if (del->getParent()->getLeft() == del)
			{
				del->getParent()->setLeft(NULL);
			}
			else if (del->getParent()->getRight() == del)
			{
				del->getParent()->setRight(NULL);
			}
			Node<Key, Value> *p = del->getParent();
			while (p)
			{
				updateHeight(p);
				p = p->getParent();
			}
			delete del;
			del = NULL;
		}
	}
	else if (del->getLeft() == NULL && del->getRight() != NULL)
	{
		Node<Key, Value> *p = NULL;
		if (del->getParent() != NULL)
		{
			p = del->getParent();
			if (del->getParent()->getRight() == del)
				del->getParent()->setRight(del->getRight()); // update right child
			else
				del->getParent()->setLeft(del->getRight()); // del->getParent()->setLeft(del->getLeft());
		}
		del->getRight()->setParent(del->getParent()); // update parent
		if (del == mRoot)
			mRoot = del->getRight();
		while (p)
		{
			updateHeight(p);
			p = p->getParent();
		}
		delete del; // delete the node
		del = NULL;
	}
	else if (del->getRight() == NULL && del->getLeft() != NULL)
	{
		Node<Key, Value> *p = NULL;
		if (del->getParent() != NULL)
		{
			p = del->getParent();
			if (del->getParent()->getRight() == del)
				del->getParent()->setRight(del->getLeft()); // update right child
			else
				del->getParent()->setLeft(del->getLeft());
		}
		del->getLeft()->setParent(del->getParent()); // update parent
		if (del == mRoot)
			mRoot = del->getLeft();
		while (p)
		{
			updateHeight(p);
			p = p->getParent();
		}
		delete del; // delete the node
		del = NULL;
	}
	else
	{														  // the node has two children
		Node<Key, Value> *tmp = maxValueNode(del->getLeft()); // set tmp as the predecessor
		if (tmp->getParent() == del)
		{
			if (del->getParent())
			{
				if (del->getParent()->getRight() == del)
				{
					del->getParent()->setRight(tmp);
				}
				else
				{
					del->getParent()->setLeft(tmp);
				}
			} // set del's parent's child
			tmp->setParent(del->getParent());
			tmp->setRight(del->getRight());
			tmp->getRight()->setParent(tmp);
			// delete del;
			if (del == mRoot)
				mRoot = tmp;
			Node<Key, Value> *t = tmp;
			while (t)
			{
				updateHeight(t);
				t = t->getParent();
			}
			delete del;
			del = NULL;
		}
		else
		{
			Node<Key, Value> *p = tmp->getParent();
			if (tmp->getLeft())
			{
				tmp->getLeft()->setParent(tmp->getParent());
			}
			tmp->getParent()->setRight(tmp->getLeft());
			tmp->setLeft(del->getLeft()); // update the left node of the predecessor
			del->getRight()->setParent(tmp);
			del->getLeft()->setParent(tmp);
			if (del->getParent())
			{
				if (del->getParent()->getRight() == del)
				{
					del->getParent()->setRight(tmp);
				}
				else
				{
					del->getParent()->setLeft(tmp);
				}
			}
			tmp->setParent(del->getParent()); // update the parent of predecessor
			tmp->setRight(del->getRight());
			if (del == mRoot)
				mRoot = tmp;
			while (p)
			{
				updateHeight(p);
				p = p->getParent();
			}
			delete del;
			del = NULL;
		}
	}
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearhelper(Node<Key, Value> *node)
{
	if (node == NULL)
		return;
	clearhelper(node->getLeft());  // delete left subtree
	clearhelper(node->getRight()); // delete right subtree
	delete node;
	mRoot = NULL;
}
/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO
	clearhelper(mRoot);
}

/**
* A helper function to find the smallest node in the tree.
*/
template <typename Key, typename Value>
Node<Key, Value> *BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
	Node<Key, Value> *temp = mRoot;
	while (temp != NULL && temp->getLeft())
	{
		temp = temp->getLeft();
	}
	return temp;
}

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template <typename Key, typename Value>
Node<Key, Value> *BinarySearchTree<Key, Value>::internalFind(const Key &key) const
{
	// TODO
	Node<Key, Value> *node = mRoot;
	while (node != NULL)
	{
		if (node->getKey() == key)
			return node;
		else if (node->getKey() > key)
			node = node->getLeft();
		else if (node->getKey() < key)
			node = node->getRight();
	}
	return NULL;
}

/**
* Helper function to print the tree's contents
*/
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot(Node<Key, Value> *root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot(root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot(root->getRight());
		std::cout << "]";
	}
}

	/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
