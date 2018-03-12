#include<iostream>
#include<fstream>
#include<string>

using namespace std;
/*
5
Watermelon
test.txt
*/
bool b_search(int num,string target, string d[]);
int main(){
	int num;
	string target;
	string filename;
	cin >> num >> target >> filename;
	string* d = new string[num];
	ifstream fp;
	fp.open(filename);
	for(int i = 0 ; i < num ; i++){
		fp >> d[i];
	}
	fp.close();
	cout << b_search(num,target,d);
	return 0;
}

bool b_search(int num,string target, string d[]){
	target[0] = tolower(target[0]);
	int left = 0, right = num - 1;
	while(left <= right){
		int middle = (left + right)/2;
		if(d[middle] == target){
			return 1;
		}else if(d[middle] > target){
			right = middle - 1;
		}else{
			left = middle+1;
		}
	}
	return 0;
}
