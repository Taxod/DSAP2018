#include<iostream>
#include<cmath>
#include<string>

using namespace std;
struct np{
	int n;
	int p;
};
class big_int{
	private:
		string num;
	public:
		int len = 0;
		np cal[100]={{0}};
		big_int();
		big_int(char *c);
		big_int(string& c);
		big_int(const big_int &b);
		~big_int();	
		big_int operator+(big_int q);
		void check();
		void print();
		friend main();
};
int main(){
	string k = "17";
	string l = "100";
	big_int p(k);
	big_int q(l);
	big_int a = (p+q);
	big_int t = (a+p);
	t.print();
	return 0;
}
big_int big_int::operator+(big_int q){
	big_int result(*this);
	int biglen = len;
	int gap = abs(this->len - q.len);
	if(q.len > this->len){
		biglen = q.len;
		for(int i = len-1 ; i >= 0 ;i--){
			result.cal[i+gap].n = result.cal[i].n;
		}
		for(int i = 0 ; i < gap ; i++){
			result.cal[i].n = 0;
		}
	}else if(q.len < this->len){
		for(int i = q.len-1 ; i >= 0 ;i--){
			q.cal[i+gap].n = q.cal[i].n;
		}
		for(int i = 0 ; i < gap ; i++){
			q.cal[i].n = 0;
		}
	}
	result.len = biglen;
	for(int i = 0 ; i < biglen ; i++){
		result.cal[i].n += q.cal[i].n;
	}
	for(int i = 0 ; i < biglen;i++){
		result.cal[i].p = len-1-i;
	}
	result.check();
	return result;
} 
big_int::big_int(){
}
big_int::big_int(const big_int &b){
	num = b.num;
	len = b.len;
	for(int i = 0 ; i < len;i++){
		cal[i] = b.cal[i];
	}
}
big_int::big_int(char *c){
	num = c;
	len = num.length();
	for(int i = 0 ; i < len;i++){
		char temp = num[i];
		cal[i].n = atoi(&temp);
		cal[i].p = len-1-i;
	}
}
big_int::big_int(string& c){
	num = c;
	len = num.length();
	for(int i = 0 ; i < len;i++){
		char temp = num[i];
		cal[i].n = atoi(&temp);
		cal[i].p = len-1-i;
	}
}
big_int::~big_int(){
}
void big_int::check(){
	for(int i = len-1 ; i >= 0 ; i--){
		if(cal[i].n >= 10){
			if(i == 0){
				for(int j = len-1; j >= 0 ; j--){
					cal[j+1].n = (cal[j].n)%10; 
				}
				cal[i].n = 1;
				len++;
				for(int i = 0 ; i < len;i++){
					cal[i].p = len-1-i;
				}
			}else{
				cal[i-1].n ++;
				cal[i].n %= 10;
			}
		}
	}
}
void big_int::print(){
	for(int i = 0 ; i < len ; i++){
		cout << cal[i].n << " ";
	}
	cout <<endl;
	for(int i = 0 ; i < len ; i++){
		cout << cal[i].p << " ";
	}
	cout <<endl;
}
