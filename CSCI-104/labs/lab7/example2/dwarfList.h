#ifndef DWARFLIST_H
#define DWARFLIST_H

#include <string>
#include <stdexcept>

class OutOfBounds : public std::exception 
{
public:
  OutOfBounds(int i) 
  : msg("OutOfBounds: There is no index " + std::to_string(i))
  {
  }
  virtual const char* what() const noexcept
  {
    return msg.c_str();
  }
private:
  std::string msg;
};

class DwarfList
{
public:
	DwarfList();
	~DwarfList();
	void add(const std::string& dwarf);
	const std::string& get(int index) const;
private:
	std::string* mDwarfList;
	int mSize;
	int mCapacity;
};

#endif
