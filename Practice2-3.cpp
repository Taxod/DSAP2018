#include<iostream>
#include<string>

using namespace std;

string toDollarNumber(int value);

int main(){
//	int p = 123456789;
	int p;
	cin >> p;
	cout << toDollarNumber(p);
	return 0;
}
string toDollarNumber(int value){
	string p = to_string(value);
	int len = p.length();
	if(len%3 == 0){
		for(int i = 0 ; i < (len/3)-1 ; i++){
			p.insert( len - 3*(i+1),",");
		}	
	}else{
		for(int i = 0 ; i < len/3 ; i++){
			p.insert( len - 3*(i+1),",");
		}
	}
	p.insert(0,"$");
	return p;
}
