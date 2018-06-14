#include <iostream>

using namespace std;
template <typename KeyType, typename ItemType>
class DictionaryInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual int getNumberOfItems() const = 0;
	virtual bool add(const KeyType& searchKey, const ItemType& newEntry) = 0;
	virtual bool remove(const KeyType& searchKey) = 0;
	virtual void clear() const = 0;
	virtual ItemType getItem(const KeyType& searchkey) const throw(NotFoundException) = 0;
	virtual bool contains(const KeyType& searchKey) const = 0;
	virtual void traverse(void visit(ItemType&)) const = 0;
};

class Dictionary
{
public:
	Dictionary();
	~Dictionary();
	bool isEmpty() const;
	int getNumberOfItems() const;
	bool add(const KeyType& searchKey, const ItemType& newEntry);
	bool remove(const KeyType& searchKey);
	void clear() const;
	ItemType getItem(const KeyType& searchkey) const throw(NotFoundException);
	bool contains(const KeyType& searchKey) const;
	void traverse(void visit(ItemType&)) const;
};


int main(int argc, char const *argv[])
{
	return 0;
}