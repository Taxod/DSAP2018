#include <iostream>
#include<exception>
using namespace std;

int main(int argc, char const *argv[])
{
	return 0;
}

template <typename ItemType>
class stack : public stackInterface<ItemType>
{
private:
	ItemType *item;
	int top;
public:
	ArrayStack();
	~ArrayStack();
	bool isEmpty() const;
	bool push(const ItemType& newEntry);
	bool pop();
	ItemType peek() const;
}
template<typename ItemType>
ArrayStack<ItemType>::~ArrayStack(){
	delete [] item;
}
template <typename ItemType>
ArrayStack<ItemType>::ArrayStack():top(-1){
	item = new ItemType [MAX_STACK];
}
template <typename ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry){
	bool result = false;
	if (top < MAX_STACK-1)
	{
		top++;
		item[top] = newEntry;
		result = true;
	}else{
		tmp = new ItemType [MAX_STACK];
		for (int i = 0; i < MAX_STACK; ++i)
		{
			tmp[i] = item[i];
		}
		delete [] item;
		oringnal_len = MAX_STACK;
		MAX_STACK += MAX_STACK;
		item = new ItemType [MAX_STACK];
		for (int i = 0; i < oringnal_len; ++i)
		{
			item[i] = tmp[i];
		}
		top++;
		item[top] = newEntry;
		result = true;
	}
	return result;
}
