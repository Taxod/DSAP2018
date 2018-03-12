#include<iostream>
#include<string>

using namespace std;

int main(){
	string p = "Hi! Let us learn Programming together. What do you think?";
//	getline(cin,p);
	char* c = "_";
	int count = 0;
	while(true){
		if(p.find(",") != string::npos){
			p.replace(p.find(","),1,c);
			count++;
		}else if(p.find(".") != string::npos){
			p.replace(p.find("."),1,c);
			count++;
		}else if(p.find(":") != string::npos){
			p.replace(p.find(":"),1,c);
			count++;
		}else if(p.find(";") != string::npos){
			p.replace(p.find(";"),1,c);
			count++;
		}else if(p.find("!") != string::npos){
			p.replace(p.find("!"),1,c);
			count++;
		}else if(p.find("?") != string::npos){
			p.replace(p.find("?"),1,c);
			count++;
		}else{
			break;
		}
	}
	cout << count ;
	return 0;
} 
