#include "../bst.h"
#include <string>

template<typename Key, typename Value>
class InheritedBST : public BinarySearchTree<Key, Value>
{
public:
	void test();
};

template<typename Key, typename Value>
void InheritedBST<Key, Value>::test() 
{
	Node<Key, Value>* node = this->internalFind(this->mRoot->getKey());
	Node<Key, Value>* smallest = this->getSmallestNode();
	if (node == smallest)
	{
		this->printRoot(this->mRoot);
	}
}

void testProtectedMembers()
{
	InheritedBST<int, double> bst;
	bst.test();
}

void testPublicFunctions()
{
	BinarySearchTree<std::string, int> bst;
	int height = bst.height();
	bool balanced = bst.isBalanced();
	if (height == 0 && balanced)
	{
		bst.insert(std::pair<const std::string, int>("a", 5));
		bst.remove("a");
	}
	bst.print();
	bst.clear();
}

int main(int argc, char* argv[])
{
	testPublicFunctions();
	testProtectedMembers();
	return 0;
}