#ifndef CHECK_SPLAY_H
#define CHECK_SPLAY_H

#include "user_bst_headers.h"
#include "check_bst.h"


/*
 * Determines the node that would be "last visited" if the given
 * key was looked up in the tree.  If the node exists, this returns its
 * parent.  If the node does not exist, this returns the last node
 * that would be considered in a standard BST search before determine that
 * the node does not exist in the tree.
 */

template<typename Key, typename Value>
Node<Key, Value> * getLastVisitedNode(BinarySearchTree<Key, Value> & tree, Key & searchedKey)
{
	if(tree.mRoot==NULL){
		return NULL;
	}
	Node<Key, Value>* lastVisited = tree.mRoot;
	bool found = false;
	bool end = false;
	while(!found && !end){
		if(lastVisited->getKey()==searchedKey){
			found = true;
		}
		else if(lastVisited->getKey()> searchedKey){
			if(lastVisited->getLeft()!=NULL){
				lastVisited= lastVisited->getLeft();
			}
			else{
				end=true;
			}
		}
		else{
			if(lastVisited->getRight()!=NULL){
				lastVisited = lastVisited->getRight();
			}
			else{
				end = true;
			}
		}
	}
	if(found){
		return lastVisited->getParent();
	}
	return lastVisited;
}


/*
 * Removes the given key, and checks that the node has been removed.
 *
 * On failure, should print useful debug messages that tell the user what node was removed and what should have been splayed,
 * then print the tree and return false.
 */
template<typename Key, typename Value>
bool checkedRemove(SplayTree<Key, Value> & tree, Key const & toRemove)
{
	Node<Key, Value>* aboutToBeRemoved = tree.internalFind(toRemove);
	if(aboutToBeRemoved != nullptr){
		if(!(aboutToBeRemoved->getLeft()!=NULL && aboutToBeRemoved->getRight()!=NULL)&&(!(aboutToBeRemoved->getLeft()==NULL && aboutToBeRemoved->getRight()==NULL))){
					std::cout<<"Please note that the removal of "<<toRemove<<" is a removal of a node with a single child, the behavior of which was not well-defined"<<std::endl;
					std::cout<<"If you fail this removal, you may need to comment or uncomment line 10 of test_remove.cpp"<<std::endl;
					std::cout<<std::endl;
		}
	}
	tree.remove(toRemove);

	if(tree.internalFind(toRemove) != nullptr)
	{
		std::cout << "Key \"" << toRemove << "\" was supposed to have been removed, but was still found by internalFind()!" << std::endl;
		return false;
	}

	return true;
}


/*
 * Inserts the given key into the tree, and checks that it has been splayed to the root.
 * Then, it calls isValidTree() to make sure that the tree structure is correct.
 *
 * On failure, should print useful debug messages that tell the user what node was inserted, then print the tree and return false.
 */
template<typename Key, typename Value>
bool checkedInsert(SplayTree<Key, Value> & tree, std::pair<Key, Value> const & toInsert)
{
	tree.insert(toInsert);
	if(tree.mRoot->getKey()!=toInsert.first){
		std::cout<<"You didn't splay the right thing to root"<<std::endl;
		std::cout<<"Expected "<<toInsert.first<<" at root but got "<<tree.mRoot->getKey()<<" instead"<<std::endl;
		return false;
	}
	if(!verifyBST(tree)){
		std::cout<<"Something is wrong with your BST structure"<<std::endl;
		return false;
	}
	return true;
}



#endif
