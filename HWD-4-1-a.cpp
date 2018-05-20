#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	stack aStack;
	stack auxStack;
	while(!aStack.isEmpty()){
		auxStack.push(aStack.peek());
		aStack.pop();
	}
	aStack = auxStack();//need to overload operater=
	return 0;
}