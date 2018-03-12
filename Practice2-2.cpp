#include<iostream>
#include<string>

using namespace std;
/*
5
Watermelon
apple
banana
grapefruit
orange
watermelon
*/
int main(){
	int num;
	cin >> num;
	string target;
	cin >> target;
	string* d = new string [num];
	for(int i = 0 ; i < num; i++){
		cin >> d[i];
	}
	target[0] = tolower(target[0]);
	cout << target;
	return 0;
}
