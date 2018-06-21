#include "dwarfList.h"

DwarfList::DwarfList() 
: mSize(0)
, mCapacity(1)
{
	mDwarfList = new std::string[mCapacity];
}

DwarfList::~DwarfList()
{
	delete [] mDwarfList;
}

void DwarfList::add(const std::string& dwarf) 
{
	if (mSize == mCapacity)
	{
		mCapacity += 1;
		std::string* temp = new std::string[mCapacity];
		for (int i = 0; i < mSize; ++i)
		{
			temp[i] = mDwarfList[i];
		}
		delete [] mDwarfList;
		mDwarfList = temp;
	}
	mDwarfList[mSize++] = dwarf;
}

const std::string& DwarfList::get(int index) const
{
	if(index >= mSize) 
	{
		throw OutOfBounds(index);
	}
	return mDwarfList[index];
}