#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	
	return 0;
}
string stack::readandcorrect(){
	stack aStack;
	stack auxStack;
	string c;
	string s;
	while(cin >> c){
		if (c != '←')
		{
			aStack.push(c);
		}else{
			aStack.pop();
		}
	}
	while(!aStack.isEmpty()){
		auxStack.push(aStack.peek());
		aStack.pop();
	}
	while(!auxStack.isEmpty()){
		s += auxStack.peek();
		auxStack.pop();
	}
	return s;
}