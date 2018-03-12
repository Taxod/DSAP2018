#include<iostream>
#include<fstream>
#include<string>

using namespace std;
/*
Watermelon
test.txt
*/

void print (string target,string c);
bool b_search(int num,string target, string d[]);
int main(){
	int num = 0;
	string target;
	string filename;
	cin >> target >> filename;
	string* d = new string[10000];
	ifstream fp;
	fp.open(filename);
	while(fp>>d[num]){
		num++;
	}
	fp.close();
	cout << b_search(num,target,d);
	return 0;
}

bool b_search(int num,string target, string d[]){
	string Target = target;
	target[0] = tolower(target[0]);
	int left = 0, right = num - 1;
	while(left <= right){
		int middle = (left + right)/2;
		if(d[middle] == target){
			print(Target,d[middle]);
			cout << "... Got it!";
			return 1;
		}else if(d[middle] > target){
			print(Target,d[middle]);
			cout << endl;
			right = middle - 1;
		}else{
			print(Target,d[middle]);
			cout << endl;
			left = middle+1;
		}
	}
	return 0;
}
void print (string target,string c){
	cout << "Comparing " << target << " with " << c;
}
