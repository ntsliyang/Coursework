#include "llist.h"
#include <cstddef>

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
  return mItem->next;
}

template <typename T>
typename LList<T>::iterator& LList<T>::iterator::operator--()
{
  return mItem->prev;
}

template <typename T>
typename T& LList<T>::iterator::operator*()
{
  return mItem->val;
}

template <typename T>
typename T* LList<T>::iterator::operator->()
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