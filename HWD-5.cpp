#include <iostream>
#include<string>

using namespace std;

int main(int argc, char const *argv[])
{
	return 0;
}

bool isLanguageL(string s){
	stack aStack;
	for (int i = 0; i < s.length(); ++i)
	{
		char first_c = s[0];
		char second_c = 0;
		bool second = 0;
		if (s[i] == first_c)
		{
			aStack.push(s[i])
		}else{
			if (second == false)
			{
				second_c = s[i]
				aStack.pop();
				aStack.pop();
			}else{
				return false;
			}
		}
	}
	if (aStack.isEmpty())
	{
		return true;
	}else{
		return false;
	}
}