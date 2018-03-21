#include<iostream>
#include<cmath>
#include<math.h>
#include<string>
#include <stdlib.h>

using namespace std;
struct np{
	int n;
	int p;
};
class big_int{
	private:
		string num;
		bool negative = false; 
	public:
		int len = 0;
		np cal[100]={{0}};
		big_int();
		big_int(string& c);
		big_int(const big_int &b);
		~big_int();	
		big_int operator+(big_int q);
		big_int operator-(big_int q);
		big_int operator*(big_int q);
		bool operator>(big_int q);
		bool operator<(big_int q);
		bool operator==(big_int q);
		void operator=(big_int q);
		big_int abs();
		void square();
		void check();//新增負數檢查
		void print();
		friend main();
};
int main(){
	string k = "199";
	string l = "-99";

	big_int p(k);
	big_int q(l);
	// q.print();
	// p.square();
	// p.print();
	// cout << (p==q);
	big_int t = p + q;
	t.print();
	return 0;
}
bool big_int::operator==(big_int q){
	if (this->negative != q.negative)
	{
		return false;
	}
	if (this->len == q.len)
	{
		for (int i = 0; i < this->len; ++i)
		{
			if (this->cal[i].n != q.cal[i].n)
			{
				return false;
			}
		}
		return true;
	}else{
		return false;
	}
}
bool big_int::operator>(big_int q){
	if (this->negative == false && q.negative == true)
	{
		return true;
	}else if (this->negative == true && q.negative == false)
	{
		return false;
	}
	if (this->len > q.len)
	{
		return true;
	}else if (this->len < q.len)
	{
		return false;
	}else{
		if (this->cal[0].n > q.cal[0].n)
		{
			return true;
		}else{
			return false;
		}
	}
}
bool big_int::operator<(big_int q){
	return !(*this > q);
}

big_int big_int::abs(){
	if (this->negative == true)
	{
		for (int i = 0; i < this->len; ++i)
		{
			this->cal[i].n = this->cal[i].n*-1;
		}
	}
	this->negative = false;

	
	return *this;
}
void big_int::square(){
	*this = *this * *this;
	this->negative = false;
}
big_int big_int::operator-(big_int q){
	big_int result;
	if ((this->negative == false && q.negative == false))
	{
		result = q;
		for (int i = 0; i < result.len; ++i)
		{
			result.cal[i].n *= -1; 
		}
		result = result + *this;
		if (this->abs() < q.abs())
		{
			result.negative = true;
		}
		return result;
	}else if ((this->negative == true && q.negative == true))
	{
		result = *this;
		for (int i = 0; i < result.len; ++i)
		{
			result.cal[i].n *= -1; 
		}
		result = result + q;
		if (this->abs() > q.abs())
		{
			result.negative = true;
		}
		return result;
	}else if ( this->negative == false && q.negative == true)
	{
		for (int i = 0; i < q.len; ++i)
		{
			q.cal[i].n *= -1; 
		}
		result = *this + q;
		return result;
	}else{
		for (int i = 0; i < q.len; ++i)
		{
			q.cal[i].n *= -1; 
		}
		result = *this + q;
		result.negative = true;
		return result;
	}
	
}
big_int big_int::operator*(big_int q){
	big_int result;
	if (this->negative == false)
	{
		if (q.negative == true)
		{
			result.negative = true;		
		}
	}else{
		if (q.negative == false)
		{
			result.negative = true;
		}
	}

	result.len = this->cal[0].p + q.cal[0].p + 1 ;
	int temp = q.cal[0].n * this->cal[0].n;
	while(temp >= 10){
		temp /= 10;
		result.len++;
	}
	for(int i = 0 ; i < result.len;i++){
		result.cal[i].p = result.len-1-i;
	}
	for (int i = 0; i < this->len; ++i)
	{
		for (int j = 0; j < q.len; ++j)
		{
			int poly = this->cal[i].p + q.cal[j].p;
			int ntmp = this->cal[i].n*q.cal[j].n;
			result.cal[result.len-poly-1].n += ntmp;
		}
		result.check();
	}
	
	return result;
}
big_int big_int::operator+(big_int q){//需要修改
	big_int result(*this);
	int biglen = this->len;
	// if (this->negative == false && this->abs() < q.abs())
	// {
	// 	result.negative = true;
	// }else if (this->negative == true)
	// {	
	// 	if (this->abs() > q.abs() || q.negative == true)
	// 	{
	// 		result.negative = true;
	// 	}
	// }else{
	// 	result.negative = false;
	// }
	if (q.len > biglen)
	{
		biglen = q.len;
		result = q;
		for (int i = 0; i < biglen; ++i)
		{
			for (int j = 0; j < this->len; ++j)
			{
				if (result.cal[i].p == this->cal[j].p)
				{
					result.cal[i].n += this->cal[j].n;
				}
			}
		}
	}else{
		for (int i = 0; i < biglen; ++i)
		{
			for (int j = 0; j < q.len; ++j)
			{
				if (result.cal[i].p == q.cal[j].p)
				{
					result.cal[i].n += q.cal[j].n;
				}
			}
		}
	}
	result.check();
	return result;
}
void big_int::operator=(const big_int q){
	this->len = q.len;
	this->negative = q.negative;
	for (int i = 0; i < q.len; ++i)
	{
		this->cal[i] = q.cal[i];
	}
	this->num = q.num;
}
big_int::big_int(){
	len = 0;
	negative = false;
}
big_int::big_int(const big_int &b){
	negative = b.negative;
	num = b.num;
	len = b.len;
	for(int i = 0 ; i < len;i++){
		cal[i] = b.cal[i];
	}
}
big_int::big_int(string& c){
	if (c[0] == '-')
	{
		negative = true;
		c = c.substr(1);
		num = c;
		len = num.length();
		for(int i = 0 ; i < len;i++){
			char temp = num[i];
			cal[i].n = atoi(&temp)*(-1);
			cal[i].p = len-1-i;
		}
	}else{
		negative = false;
		num = c;
		len = num.length();
		for(int i = 0 ; i < len;i++){
			char temp = num[i];
			cal[i].n = atoi(&temp);
			cal[i].p = len-1-i;
		}
	}
	
}
big_int::~big_int(){
}
void big_int::check(){
	for(int i = len-1 ; i >= 0 ; i--){
		if(cal[i].n >= 10){
			if(i == 0){
				// for(int j = len-1; j >= 0 ; j--){
				// 	cal[j+1].n = (cal[j].n)%10; 
				// }
				for(int j = len-1; j >= 0 ; j--){
					cal[j+1].n = (cal[j].n); 
				}
				cal[i].n = cal[i+1].n/10;
				cal[i+1].n%=10;
				len++;//更新長度
				//更新位數
				for(int i = 0 ; i < len;i++){
					cal[i].p = len-1-i;
				}
			}else{
				// cal[i-1].n ++;
				cal[i-1].n += (cal[i].n/10);
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
	cout << "negative" << this->negative<<endl;
}
/*
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
} */