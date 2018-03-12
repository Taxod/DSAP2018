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
	int left = 0, right = num - 1;
	while(left <= right){
		int middle = (left + right)/2;
		if(d[middle] == target){
			cout << 1;
			return 0;
		}else if(d[middle] > target){
			right = middle - 1;
		}else{
			left = middle+1;
		}
	}
	cout << 0;
//	cout << target;
	return 0;
}
