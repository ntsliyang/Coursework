#include "llist.h"

template<class T> 
template<typename Item> 
  LList::Item::Item(const T& v, Item* p, Item* n)
: val(v), prev(p), next(n)
{
}

template<typename T> 
LList::LList() {
  mHead = new Item(T(), nullptr, nullptr);
  mTail = mHead;
  mSize = 0;
}

template<typename T> 
LList::LList(const LList& other) {
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
LList& LList::operator=(const LList& other) {
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
LList::~LList() {
  clear();
  delete mHead;
}

template<typename T> 
int LList::size() const {
  return mSize;
}

template<typename T> 
bool LList::empty() const {
  return mSize == 0;
}

template<typename T> 
void LList::push_back(const T& val) {
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
T& LList::get(int loc) {
  Item *temp = getNodeAt(loc);
  return temp->val;
}

template<typename T> 
const T& LList::get(int loc) const {
  Item *temp = getNodeAt(loc);
  return temp->val;
}

template<typename T> 
void LList::clear() {
  while(mHead != mTail) {
    Item *temp = mHead->next;
    delete mHead;
    mHead = temp;
  }
  mSize = 0;
}

template<typename T> 
LList::Item* LList::getNodeAt(int loc) const {
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
