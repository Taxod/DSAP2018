#include<iostream>
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
		int len = num.length();
		np cal[100]={{0}};
		big_int();
		big_int(char *c);
		big_int(string& c);
		~big_int();
		friend main();
};
int main(){
	string k = "1111111111";
	big_int p(k);
	big_int q(k);
	
	
	for(int i = 0 ; i < p.len ; i++){
		cout << p.cal[i].n<<" ";
	}
	cout << endl;
	for(int i = 0 ; i < p.len ; i++){
		cout << p.cal[i].p<<" ";
	}
	return 0;
}
big_int operator+(big_int p,big_int q){
	big_int result;
	int biglen = p.len;
	if(q.len > p.len){
		biglen = q.len;
	}
	for(int i = 0 ; i < biglen ; i++){
		
	}
	return result;
} 
big_int::big_int(){
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
