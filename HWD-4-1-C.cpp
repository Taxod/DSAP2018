#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	stack aStack;
	stack auxStack;
	ItemType specified_item;
	while(!aStack.isEmpty()){
		if (aStack.peek() != specified_item)
		{
			auxStack.push(aStack.peek());
		}
		aStack.pop();
	}
	while(!auxStack.isEmpty()){
		aStack.push(auxStack.peek());
		auxStack.pop();
	}
	return 0;
}