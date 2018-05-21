#include <iostream>
#include<exception>
using namespace std;

int main(int argc, char const *argv[])
{
	return 0;
}

template <typename ItemType>

void ArrayStack<ItemType>::push(const ItemType& newEntry){
	try{
		if (top < MAX_STACK-1)
		{
		top++;
		item[top] = newEntry;
		}else{
			throw(exception);
		}
	}
}