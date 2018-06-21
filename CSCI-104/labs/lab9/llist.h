// TODO(1): Template LList class, as well as all the functions inside it
// Change appropriate mentions of int to the templated typename
#include <cstddef>

template<class T> 
class LList {

private:
  // TODO(2): What needs to happen in Item?
  struct Item {
    Item(const T& v, Item* p, Item* n);
    T val;
    Item *prev;
    Item *next;
  };

public:
  // TODO(2): What needs to happen in iterator?
  class iterator {
    friend LList;
  public:
    iterator();
    iterator& operator++();
    iterator& operator--();
    T& operator*();
    T* operator->();
    bool operator==(iterator other);
    bool operator!=(iterator other);
  private:
    iterator(Item* item);
    Item* mItem;
  };

  LList();
  LList(const LList& other);
  LList& operator=(const LList& other);
  ~LList();

  // TODO(3): Change the signatures of these methods appropriately
  int size() const;
  bool empty() const;
  void push_back(const T& val);
  T& get(int pos);
  const T& get(int pos) const;
  void clear();

  iterator begin();
  iterator end();

private:
  Item* getNodeAt(int pos) const;

  Item* mHead;
  Item* mTail;
  int mSize;
};

// TODO(4): Copy the contents of llist.cpp here and fix their signature
template<typename T> 
LList<T>::Item::Item(const T& v, Item* p, Item* n)
: val(v), prev(p), next(n)
{
}

template<typename T> 
LList<T>::LList() {
  mHead = new Item(T(), nullptr, nullptr);
  mTail = mHead;
  mSize = 0;
}

template<typename T> 
LList<T>::LList(const LList& other) {
  mHead = new Item(T(), nullptr, nullptr);
  mTail = mHead;
  mSize = 0;
  Item* temp = other.mHead;
  while(temp != other.mTail){
    push_back(temp->val);
    temp = temp->next;
  }
}

template<typename T> 
LList<T>& LList<T>::operator=(const LList& other) {
  if(this == &other){
    return *this;
  }
  clear();
  Item* temp = other.mHead;
  while(temp != other.mTail){
    push_back(temp->val);
    temp = temp->next;
  }
  return *this;
}

template<typename T> 
LList<T>::~LList() {
  clear();
  delete mHead;
}

template<typename T> 
int LList<T>::size() const {
  return mSize;
}

template<typename T> 
bool LList<T>::empty() const {
  return mSize == 0;
}

template<typename T> 
void LList<T>::push_back(const T& val) {
  Item* n = new Item (val, mTail->prev, mTail);
  if(mHead == mTail){
    mHead = n;
  }
  else
  {
    mTail->prev->next = n;
  }
  mTail->prev = n;
  ++mSize;
}

template<typename T> 
T& LList<T>::get(int loc) {
  Item *temp = getNodeAt(loc);
  return temp->val;
}

template<typename T> 
const T& LList<T>::get(int loc) const {
  Item *temp = getNodeAt(loc);
  return temp->val;
}

template<typename T> 
void LList<T>::clear() {
  while(mHead != mTail) {
    Item *temp = mHead->next;
    delete mHead;
    mHead = temp;
  }
  mSize = 0;
}

template<typename T>  
typename LList<T>::Item* LList<T>::getNodeAt(int loc) const {
  if(loc >= 0 && loc < mSize){
    Item *temp = mHead;
    while(loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    return nullptr;
  }
}


// TODO(5): Copy the content of iterator.h here
template <typename T>
typename LList<T>::iterator LList<T>::begin()
{
  return LList<T>::iterator(mHead);
}

template <typename T>
typename LList<T>::iterator LList<T>::end()
{
  return LList<T>::iterator(mTail);
}

template <typename T>
LList<T>::iterator::iterator()
: mItem(nullptr)
{
}

template <typename T>
LList<T>::iterator::iterator(Item* item)
: mItem(item)
{
}

// TODO(6): Implement operator++ and operator--
template <typename T>
typename LList<T>::iterator& LList<T>::iterator::operator++() 
{
  mItem = mItem->next;
  return *this;
}

template <typename T>
typename LList<T>::iterator& LList<T>::iterator::operator--()
{
  mItem = mItem->prev;
  return *this;
}

template <typename T>
T& LList<T>::iterator::operator*()
{
  return mItem->val;
}

template <typename T>
T* LList<T>::iterator::operator->()
{
  return &mItem->val;
}

template <typename T>
bool LList<T>::iterator::operator==(typename LList<T>::iterator other)
{
  return mItem == other.mItem;
}

template <typename T>
bool LList<T>::iterator::operator!=(typename LList<T>::iterator other)
{
  return mItem != other.mItem;
}