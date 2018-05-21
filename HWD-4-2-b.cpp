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

while(輸入字元){
	push進astack
}
while(aStack不是空的){
	將astack的物件放入auxstack
	把物件從astack，pop
}
while(auxStack不是空的){
	印出物件
	pop物件從auxstack
}