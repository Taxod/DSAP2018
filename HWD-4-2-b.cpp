#include <iostream>
#include<string>
using namespace std;

int main(int argc, char const *argv[])
{
	char c;
	stack aStack;
	stack auxStack;
	while(cin >> c){
		aStack.push(c);
	}
	while(!aStack.isEmpty()){
		auxStack.push(aStack.peek());
		aStack.pop();
	}
	aStack = auxStack;
	return 0;
}