// check_bst.h - implements functions to check that BSTs are correct and valid

#ifndef CHECK_BST_H
#define CHECK_BST_H

#include <set>
#include <iostream>

#include "user_bst_headers.h"
#include "print_bst.h"

using namespace std;


/* Verifies that tree is a valid binary tree.
   That is, each node is greater than its
   predecessor in the tree structure, and
   the parent->child and child->parent pointers
   of all nodes match up.

   This function should **gracefully**
   deal with errors in the tree structure, and
   print a helpful error message telling the user
   what is wring when it finds one.

   Return value is true if the tree is valid, and false if it is not.
*/
template<typename Key, typename Value>
bool isValidTree(BinarySearchTree<Key, Value> & tree)
{
	// empty trees are always valid
	if(tree.mRoot == nullptr)
	{
		return true;
	}
	else
	{
		return checkValidTraversal(tree.mRoot);
	}
}

template<typename Key, typename Value>
bool checkValidTraversal(Node<Key, Value>* current){
		if(current->getLeft()!=NULL){
			if(!(current->getLeft()->getKey() < current->getKey())){
				cout<<"The left child of "<<current->getKey()<<" is "<<current->getLeft()->getKey()<<" which is larger than its parent and not allowed for a left child in a BST"<<endl;
				return false;
			}
			if(current->getLeft()->getParent()!=current){
				cout<<"The left child of "<<current->getKey()<<" does not have its parent set correctly"<<endl;
				return false;
			}
			Node<Key, Value>* predecessor = current->getLeft();
			while(predecessor->getRight()!=NULL){
				predecessor = predecessor->getRight();
			}
			if(!(predecessor->getKey()< current->getKey())){
				cout<<"The prececessor of "<<current->getKey()<<" is "<< predecessor->getKey()<<" which is larger than what it is predecessing"<<endl;
				return false;
			}
			if(!checkValidTraversal(current->getLeft())){
				return false;
			}
		}
		if(current->getRight()!=NULL){
			if(!(current->getKey() < current->getRight()->getKey())){
				cout<<"The right child of "<<current->getKey()<<" is "<<current->getRight()->getKey()<<" which is less than its parent and not allowed for a right child"<<endl;
				return false;
			}
			if(current->getRight()->getParent()!=current){
				cout<<"the right child of "<<current->getKey()<<" does not have its parent set correctly"<<endl;
				return false;
			}
			if(!checkValidTraversal(current->getRight())){
				return false;
			}
		}
		return true;
}


/* Verifies that the given tree contains the
   keys given by the key set, in their natural order.

   The passed tree is guaranteed to be valid according to
   isValidTree(), so an iterator can be used for this function.

   Returns true on success, false on failure.
*/
template<typename Key, typename Value>
bool checkKeys(BinarySearchTree<Key, Value> & tree, std::set<Key> const & keySet)
{
  for (typename std::set<Key>::iterator it = keySet.begin(); it != keySet.end(); ++it)
  {
      typename BinarySearchTree<Key, Value>::iterator keyToFind = typename BinarySearchTree<Key, Value>::iterator(tree.internalFind(*it));
      if (keyToFind == tree.end())
      {
    	  std::cerr << "Tree should contain key " << *it << ", but it was not found!" << std::endl;
    	  std::cerr << "NOTE: BST internalFind() was used for checking, not SplayTree::find()" << std::endl;
          return false;
      }
  }
  return true; 
}

// recursive helper function for below function
template<typename Key, typename Value>
bool checkStructureRecursive(Node<Key, Value> * expectedNode, Node<Key, Value> * actualNode)
{

	// compare items
	if(expectedNode->getItem().first != actualNode->getItem().first)
	{
		std::cerr << "Node mismatch!  Expected (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << "), got ("
				<< actualNode->getItem().first << ", " << actualNode->getItem().second << ")" << std::endl;

		return false;
	}

	// note; we don't compare the heights since those are verified as right by verifyBST()

	// compare existance/nonexistance of children
	if(expectedNode->getRight() == nullptr)
	{
		if(actualNode->getRight() != nullptr)
		{
			std::cerr << "Node (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << ") is not supposed to have a right child, but instead it has ("
				<< actualNode->getRight()->getItem().first << ", " << actualNode->getRight()->getItem().second << ")"<< std::endl;
		}
	}
	else
	{
		if(actualNode->getRight() == nullptr)
		{
			std::cerr << "Node (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << ") is supposed to have a right child, ("
				<< expectedNode->getRight()->getItem().first << ", " << actualNode->getRight()->getItem().second << "), but instead it has no right child"<< std::endl;
		}
		else
		{
			// recurse to right child
			if(!checkStructureRecursive(expectedNode->getRight(), actualNode->getRight()))
			{
				return false;
			}
		}
	}

	if(expectedNode->getLeft() == nullptr)
	{
		if(actualNode->getLeft() != nullptr)
		{
			std::cerr << "Node (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << ") is not supposed to have a left child, but instead it has ("
				<< actualNode->getLeft()->getItem().first << ", " << actualNode->getLeft()->getItem().second << ")"<< std::endl;
		}
	}
	else
	{
		if(actualNode->getLeft() == nullptr)
		{
			std::cerr << "Node (" << expectedNode->getItem().first << ", " << expectedNode->getItem().second << ") is supposed to have a left child, ("
				<< expectedNode->getLeft()->getItem().first << ", " << actualNode->getLeft()->getItem().second << "), but instead it has no left child"<< std::endl;
		}
		else
		{
			// recurse to right child
			if(!checkStructureRecursive(expectedNode->getLeft(), actualNode->getLeft()))
			{
				return false;
			}
		}
	}

	// passed the gauntlet!
	return true;
}

/* Returns true iff two BSTs contain the same data AND 
   have the same node structure.  As in, these would be
   equal:
              [20]                 [20]
              /  \        and      /  \
           [08]  [37]           [08]  [37]

   but these would be unequal:

              [20]                 [37]
              /  \        and      /  
           [08]  [37]           [20]  
                                /
                             [08]

   They must contain the same keys, and are not
   allowed to have different internal node structures.

   The passed trees are guaranteed to be valid according to
   isValidTree(), so iterators can be used for this function.

   Prints error messages where differences are found between trees.
*/
template<typename Key, typename Value>
bool checkSameStructure(BinarySearchTree<Key, Value> & expected, BinarySearchTree<Key, Value> & actual)
{
	if(expected.mRoot == nullptr)
	{
		if(actual.mRoot != nullptr)
		{
			std::cerr << "Tree is supposed to be empty, but instead it has root (" << actual.mRoot->getItem().first << ", " << actual.mRoot->getItem().second << ")" << std::endl;
		}
	}
	else
	{
		if(actual.mRoot == nullptr)
		{
			std::cerr << "Tree is supposed to have root (" << expected.mRoot->getItem().first << ", " << expected.mRoot->getItem().second << "), but instead it is empty!" << std::endl;
		}
		else
		{
			// recursively compare rest of tree
			if(!checkStructureRecursive(expected.mRoot, actual.mRoot))
			{
				return false;
			}
		}
	}

	return true;
}

/* Top-level testing function.
   Makes sure that the passed tree is valid and consistent,
   and prints an error if it is not.

   Then, it checks the values against the provided value set, and
   prints an error if there is a mismatch.

   Returns true iff there are no errors.
*/ 

template<typename Key, typename Value>
bool verifyBST(BinarySearchTree<Key, Value> & tree, std::set<Key> const & keySet)
{
	bool error = false;

	if(!isValidTree(tree))
	{
		std::cerr << ">> Binary tree structure is broken!" << std::endl;
		error = true;
	}

	if(!error && !checkKeys(tree, keySet))
	{
		std::cerr << ">> Key mismatch error!" << std::endl;
		error = true;
	}

	if(error)
	{
		std::cerr << ">> Tree was:" << std::endl;
		prettyPrintBST(tree);
		return false;
	}
	else
	{
		//std::cout << "Tree passed verification!" << std::endl;
		return true;
	}
}

// similar to above, but only checks heights and validity, not keys.
template<typename Key, typename Value>
bool verifyBST(BinarySearchTree<Key, Value> & tree)
{
	bool error = false;

	if(!isValidTree(tree))
	{
		std::cerr << ">> Binary tree structure is broken!" << std::endl;
		error = true;
	}

	if(error)
	{
		std::cerr << ">> Tree was:" << std::endl;
		prettyPrintBST(tree);
		return false;
	}
	else
	{
		//std::cout << "Tree passed verification!" << std::endl;
		return true;
	}
}

#endif
