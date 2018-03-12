#include<iostream>
#include<string>

using namespace std;

int main(){
//	string p = "Hi! Let us learn Programming together. What do you think?";
	string p;
	getline(cin,p);
	char* c = "_";
	int count = 0;
	string pun = ",.:;!?";
	int index = 0;
	while(true){
		if(p.find(pun[index]) != string::npos){
			p.replace(p.find(pun[index]),1,c);
			count++;			
		}else{
			index++;
		}
		if(index == (pun.length())){
			break;
		}
	}
	cout << count ;
	return 0;
} 
