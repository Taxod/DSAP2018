#include <iostream>
#include<string>
using namespace std;

bool ex(char c,string str){
	for(int i = 0 ; i < str.length();i++){
		if(c == str[i]){
			return true;
		}
	}
	return false;
}
int main(){
	char c = '\0';
	string s = "12345";
	cout << ex(c,s);
	return 0;
}
