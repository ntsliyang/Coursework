#include "../bst.h"
#include <string>

template<typename Key, typename Value>
class InheritedNode : public Node<Key, Value>
{
public:
	InheritedNode(const Key& key, const Value& value);
	void test();
};

template<typename Key, typename Value>
InheritedNode<Key, Value>::InheritedNode(const Key& key, const Value& value) 
: Node<Key, Value>(key, value, nullptr)
{
}

template<typename Key, typename Value>
void InheritedNode<Key, Value>::test() 
{
	std::pair<const Key, Value> item = this->mItem;
	InheritedNode<Key, Value>* parent = static_cast<InheritedNode<Key, Value>*>(this->mParent);
	InheritedNode<Key, Value>* left = static_cast<InheritedNode<Key, Value>*>(this->mLeft);
	InheritedNode<Key, Value>* right = static_cast<InheritedNode<Key, Value>*>(this->mRight);
	left = right;
	right = parent;
	parent = left;
	if (parent->mItem.first == item.first)
	{
		parent->mItem.second = item.second;
	}
}

void testProtectedMembers()
{
	InheritedNode<int, double> node(25, 3.5);
	node.test();
}

template<typename Key, typename Value>
void testConstFunctions(const Node<Key, Value>& node)
{
	std::pair<const std::string, int> item = node.getItem();

	if (node.getKey() == item.first 
		&& node.getValue() == item.second
		&& node.getHeight() == 0)
	{
		Node<Key, Value>* parent = node.getParent();
		Node<Key, Value>* left = node.getLeft();
		Node<Key, Value>* right = node.getRight();
		parent = left;
		left = right;
		right = parent;
	}
}

template<typename Key, typename Value>
void testNonConstFunctions(Node<Key, Value>& node)
{
	std::pair<const std::string, int>& item = node.getItem();
	item.second = node.getValue();
	node.getValue() = item.second;
	node.setParent(nullptr);
	node.setLeft(nullptr);
	node.setRight(nullptr);
	node.setValue(node.getValue());
	node.setHeight(20);
}

void testPublicFunctions()
{
	Node<std::string, int> node("a", 1, nullptr);
	testNonConstFunctions<std::string, int>(node);
	testConstFunctions<std::string, int>(node);
}

int main(int argc, char* argv[]) 
{
	testPublicFunctions();
	testProtectedMembers();
	return 0;
}