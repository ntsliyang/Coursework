#include <iostream>
#include <vector>

template <typename T>
struct Item
{
	T val;
	Item<T> *left;
	Item<T> *right;
};

template <typename T>
class BSTree
{
  public:
	BSTree();
	~BSTree();
	bool search(const T &value);
	bool empty();
	int size();
	void insert(const T &value);
	std::vector<T> inOrderTraversal();
	std::vector<T> preOrderTraversal();
	std::vector<T> postOrderTraversal();

  private:
	// Helper functions that a user should not have access to
	bool searchInTree(Item<T> *node, const T &value);
	Item<T> *insertInTree(Item<T> *node, const T &value);
	void inOrderTraversalHelper(std::vector<T> &list, Item<T> *node);
	void preOrderTraversalHelper(std::vector<T> &list, Item<T> *node);
	void postOrderTraversalHelper(std::vector<T> &list, Item<T> *node);
	void insertInTreeHelper(Item<T> *node, const T &value);
	bool searchInTreeHelper(Item<T> *node, const T &value);
	// Private Variables
	Item<T> *root;
	int counter;
};

template <typename T>
BSTree<T>::BSTree()
{
	root = NULL;
	counter = 0;
}

template <typename T>
BSTree<T>::~BSTree()
{
	delete root;
}

template <typename T>
bool BSTree<T>::search(const T &value)
{
	return searchInTree(root, value);
}

template <typename T>
bool BSTree<T>::searchInTreeHelper(Item<T> *node, const T &value)
{
	if (node->val > value)
	{
		if (!(node->left) && node->left->val == value)
		{
			return true;
		}
		else
		{
			searchInTreeHelper(node->left, value);
		}
	}
	else
	{
		if (!(node->right) && node->right->val == value)
		{
			return true;
		}
		else
		{
			searchInTreeHelper(node->right, value);
		}
	}
	return false;
}

template <typename T>
bool BSTree<T>::searchInTree(Item<T> *node, const T &value)
{
	// TODO
	while (node != NULL) {
		if (node->val == value) return true;
		else if (node->val > value) node = node->left;
		else if (node->val < value) node = node->right;
	}
	return false;
}

template <typename T>
bool BSTree<T>::empty()
{
	if (root == NULL)
	{
		return true;
	}
	return false;
}

template <typename T>
int BSTree<T>::size()
{
	return counter;
}

template <typename T>
void BSTree<T>::insert(const T &value)
{
	root = insertInTree(root, value);
	counter++;
}

// template <typename T>
// void BSTree<T>::insertInTreeHelper(Item<T> *node, const T &value)
// {
// 	if (root->val > value)
// 	{
// 		// go to the left
// 		if (!root->left)
// 		{
// 			root->left = node;
// 		}
// 		else
// 		{
// 			insertInTree(root->left, value);
// 		}
// 	}
// 	else
// 	{
// 		// go to the right
// 	}
// }

template <typename T>
Item<T> *BSTree<T>::insertInTree(Item<T> *node, const T &value)
{
	// TODO
	// Feel free to modify any return values or parameters.
	// You can also choose to do your work in insert() instead.
	Item<T> *temp = new Item<T>();
	temp->val = value;
	if (root == NULL)
	{
		root = temp;
	}
	else
	{
		while (node != NULL)
		{
			if (node->val < value)
			{
				if (node->right == NULL)
				{
					node->right = temp;
					break;
				}
				node = node->right;
			}
			else if (node->val > value) 
			{
				if (node->left == NULL) 
				{
					node->left = temp;
					break;
				}
				node = node->left;
			}
		}
	}
	// return root;
	return root;
}

/* In Order Traversal */
template <typename T>
std::vector<T> BSTree<T>::inOrderTraversal()
{
	std::vector<T> list;
	if (!empty())
		inOrderTraversalHelper(list, root);
	return list;
}

template <typename T>
void BSTree<T>::inOrderTraversalHelper(std::vector<T> &list, Item<T> *node)
{
	// TODO
	// implement in order
	if (!node)
		return;
	else
	{
		inOrderTraversalHelper(list, node->left);
		list.push_back(node->val);
		inOrderTraversalHelper(list, node->right);
	}
}

/* Pre Order Traversal */
template <typename T>
std::vector<T> BSTree<T>::preOrderTraversal()
{
	std::vector<T> list;
	if (!empty())
		preOrderTraversalHelper(list, root);
	return list;
}

template <typename T>
void BSTree<T>::preOrderTraversalHelper(std::vector<T> &list, Item<T> *node)
{
	// TODO
	// implement pre order
	if (!node)
		return;
	else
	{
		list.push_back(node->val);
		preOrderTraversalHelper(list, node->left);
		preOrderTraversalHelper(list, node->right);
	}
}

/* Post Order Traversal */
template <typename T>
std::vector<T> BSTree<T>::postOrderTraversal()
{
	std::vector<T> list;
	if (!empty())
		postOrderTraversalHelper(list, root);
	return list;
}

template <typename T>
void BSTree<T>::postOrderTraversalHelper(std::vector<T> &list, Item<T> *node)
{
	// TODO
	if (!node)
		return;
	else
	{
		postOrderTraversalHelper(list, node->left);
		postOrderTraversalHelper(list, node->right);
		list.push_back(node->val);
	}
}