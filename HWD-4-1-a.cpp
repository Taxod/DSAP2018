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
	while(!auxStack.isEmpty()){
		cout << auxStack.peek();
		auxStack.pop();
	}
	return 0;
}