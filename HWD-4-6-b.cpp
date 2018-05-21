#include <iostream>
#include<exception>
using namespace std;

int main(int argc, char const *argv[])
{
	return 0;
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
		
	}
	return result;
}