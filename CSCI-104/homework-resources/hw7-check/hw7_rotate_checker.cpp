#include "../rotateBST.h"
#include <string>

template<typename Key, typename Value>
class InheritedRotate : public rotateBST<Key, Value>
{
public:
	void testProtectedMembers();
	void testInheritedMembers();
};

template<typename Key, typename Value>
void InheritedRotate<Key, Value>::testProtectedMembers()
{
	Node<Key, Value>* n = nullptr;
	this->leftRotate(n);
	this->rightRotate(n);
}

template<typename Key, typename Value>
void InheritedRotate<Key, Value>::testInheritedMembers()
{
	Node<Key, Value>* root = this->mRoot;
	Node<Key, Value>* smallest = this->getSmallestNode();
	Node<Key, Value>* found = this->internalFind(root->getKey());
	if (smallest == found)
	{
		this->printRoot(root);	
	}
}

template<typename Key, typename Value>
void testConstFunctions(InheritedRotate<Key, Value>& t1, const InheritedRotate<Key, Value>& t2)
{
	bool same = t2.sameKeys(t2);
	if (same)
	{
		t2.transform(t1);
	}
}

void testPublicFunctions()
{
	InheritedRotate<int, double> t1;
	InheritedRotate<int, double> t2;
	testConstFunctions(t1, t2);
}

void testProtectedMembers()
{
	InheritedRotate<int, double> bst;
	bst.testProtectedMembers();
}

void testPublicInheritance()
{
	InheritedRotate<std::string, int> bst;
	bst.testInheritedMembers();
	int height = bst.height();
	bool balanced = bst.isBalanced();
	if (height == 0 && balanced)
	{
		bst.insert(std::pair<const std::string, int>("a", 5));
		bst.remove("a");
	}
	bst.clear();
	bst.print();
	for (InheritedRotate<std::string, int>::iterator it = bst.begin();
		it != bst.end();
		++it)
	{
		InheritedRotate<std::string, int>::iterator found = bst.find("a");
		if (found != bst.end())
		{
			found->second = 20;
		}
	}
}

int main(int argc, char* argv[])
{
	testPublicFunctions();
	testProtectedMembers();
	testPublicInheritance();
	return 0;
}