#include<iostream>
#include<string>
using namespace std;

int main(){
	int  n = 1000;
	int count = 0;
	string s;
	int t = n;
	while (t/=10){
		count++;	
	} 
	for(int i = 0 ; i < count+1 ; i++){
		s += '0';
	}
	while( n > 0){
		s[count] = char(n%10 +'0');
		count --; 
		n /= 10;
	} 
	cout <<s;
	return 0;
} 
