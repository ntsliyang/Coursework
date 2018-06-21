#include "../splayTree.h"
#include <string>

template<typename Key, typename Value>
class InheritedSplay : public SplayTree<Key, Value>
{
public:
	void test();
};

template<typename Key, typename Value>
void InheritedSplay<Key, Value>::test() 
{
	Node<Key, Value>* node = nullptr;
	this->splay(node);
}

void testProtectedMembers()
{
	InheritedSplay<int, double> bst;
	bst.test();
}

void testPublicFunctions()
{
	InheritedSplay<std::string, int> bst;
	bst.insert(std::pair<const std::string, int>("a", 5));
	bst.remove("a");
	SplayTree<std::string, int>::iterator it1 = bst.find("b");
	it1 = bst.findMin();
	it1 = bst.findMax();
	if (it1 == bst.end())
	{
		bst.deleteMinLeaf();
		bst.deleteMaxLeaf();
	}
}

int main(int argc, char* argv[])
{
	testPublicFunctions();
	testProtectedMembers();
	return 0;
}