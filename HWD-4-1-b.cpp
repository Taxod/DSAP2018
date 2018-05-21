#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	stack aStack;
	stack auxStack;
	int count = 0;
	while(!aStack.isEmpty()){
		auxStack.push(aStack.peek());
		aStack.pop();
		count++;
	}
	while(!auxStack.isEmpty()){
		aStack.push(auxStack.peek());
		auxStack.pop();
	}
	cout << count;
	return 0;
}