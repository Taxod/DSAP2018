#include<iostream>
#include<string>

using namespace std;
size_t getSpaceCount(const size_t from, const size_t to,string K);
int main(){
	string T = "123 456 879";
	cout << getSpaceCount(0,T.length(),T)<< endl;
	cout << T;	
	return 0;
}
size_t getSpaceCount(const size_t from, const size_t to,string K){
	string T = K;
	size_t found = T.find_first_of(' ');
	int count = 0;
	while(found != string::npos){
		count ++;
		T[found] = '*';
		found = T.find_first_of(' ');
	}
	return count;
}
