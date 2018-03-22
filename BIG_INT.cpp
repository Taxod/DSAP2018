#include<iostream>
#include<cmath>
#include<math.h>
#include<string>
#include <stdlib.h>

using namespace std;

string to_string(int n){
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
	return s;
}
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
		big_int operator/(big_int q);
		big_int operator%(big_int q);
		bool operator>(big_int q);
		bool operator<(big_int q);
		bool operator==(big_int q);
		void operator=(big_int q);
		void operator=(string s);
		big_int abs();
		void square();
		void check();
		void print();
		big_int merge(const big_int q);
		friend main();
};
string to_string(big_int n);
int main(){
	string k = "123546";
	string l = "123";
	big_int p(k);
	big_int q(l);
	big_int t = p%q;
	t.print();
	return 0;
}
void big_int::operator=(string s){
	big_int p(s);
	*this = p;
}
big_int big_int::operator/(big_int q){
	long long count = 0;
	big_int result;
	big_int subd(*this);
	big_int d(q);
	if (subd < d)
	{
		result = "0";
		return result;
	}
	while(subd > d || subd == d){
		subd = subd - d;
		count ++;
	}
	string c = to_string(count);
	result = c;
	return result;
}
big_int big_int::operator%(big_int q){
	big_int result;
	big_int subd(*this);
	big_int d(q);
	if (subd < d)
	{
		result = "0";
		return result;
	}
	while(subd > d || subd == d){
		subd = subd - d;
	}
	result = to_string(subd);
	return result;
}

big_int big_int::operator-(big_int q){
	big_int result;
	big_int subm;
	big_int m;
	if ((this->abs()) > (q.abs()))
	{
		subm = *this;
		m = q;
	}else{
		subm = q;
		m = *this;
	}
	if ((this->negative == false && q.negative == false))
	{
		// result = q;
		for (int i = 0; i < m.len; ++i)
		{
			m.cal[i].n *= -1; 
		}	
		result = subm.merge(m);
		if (this->abs() < q.abs())
		{
			result.negative = true;
		}
		return result;
	}else if ((this->negative == true && q.negative == true))
	{
		// result = *this;
		for (int i = 0; i < m.len; ++i)
		{
			m.cal[i].n *= -1; 
		}
		result = subm.merge(m);
		if (this->abs() > q.abs())
		{
			result.negative = true;
		}
		return result;
	}else if ( this->negative == false && q.negative == true)
	{
		result = this->merge(q);
		result.negative = false;
		return result;
	}else{
		result = this->merge(q);
		result.negative = true;
		return result;
	}
}

big_int big_int::operator+(big_int q){//需要修改
	big_int result;
	if (this->negative == q.negative)
	{
		if (this->negative == true)
		{
			result = this->merge(q);
			result.negative = true;
			return result;
		}else{
			result = this->merge(q);
			result.negative = false;
			return result;
		}
	}else{
		if (this->negative == true)
		{
			for (int i = 0; i < this->len; ++i)
			{
				this->cal[i].n *= -1;
			}
			result = this->merge(q);
			for (int i = 0; i < this->len; ++i)
			{
				this->cal[i].n *= -1;
			}
			if (this->abs() > q.abs())
			{
				result.negative = true;
			}
			return result;
		}else{
			for (int i = 0; i < q.len; ++i)
			{
				q.cal[i].n *= -1;
			}
			result = this->merge(q);
			for (int i = 0; i < q.len; ++i)
			{
				q.cal[i].n *= -1;
			}
			if (q.abs() > this->abs())
			{
				result.negative = true;
			}
			return result;
		}
	}	
}
big_int big_int::merge(const big_int q){
	big_int result(*this);
	int biglen = this->len;
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
	if (c[0] == '-'){
		negative = true;
		c = c.substr(1);
	}else{
		negative = false;
	}	
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

void big_int::print(){
	for(int i = 0 ; i < len ; i++){
		cout << cal[i].n << " ";
	}
	cout <<endl;
	for(int i = 0 ; i < len ; i++){
		cout << cal[i].p << " ";
	}
	cout <<endl;
	if (negative)
	{
		cout << "negative\n";
	}else{
		cout << "positive\n";
	}
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
	}else if (this->negative == false)
	{
		if (this->len > q.len)
		{
			return true;
		}else if (this->len < q.len)
		{
			return false;
		}else{
			for (int i = 0; i < this->len; ++i)
			{
				if (this->cal[i].n != q.cal[i].n)
				{
					if (this->cal[i].n > q.cal[i].n)
					{
						return true;
					}else{
						return false;
					}
				}
			}
			return false;
		}
	}else{
		if (this->len > q.len)
		{
			return false;
		}else if (this->len < q.len)
		{
			return true;
		}else{
			for (int i = 0; i < this->len; ++i)
			{
				if (this->cal[i].n != q.cal[i].n)
				{
					if (this->cal[i].n > q.cal[i].n)
					{
						return false;
					}else{
						return true;
					}
				}
			}
			return false;
		}
	}
	
}
bool big_int::operator<(big_int q){
	return !(*this > q);
}

big_int big_int::abs(){
	big_int result(*this);
	result.negative = false;
	return result;
}
void big_int::square(){
	*this = *this * *this;
	this->negative = false;
}
void big_int::check(){
	for (int i = len-1; i >= 0; i--)
	{
		if (cal[i].n < 0)
		{
			if (i == 0)
			{
			}else{
				cal[i].n += 10;
				cal[i-1].n --;
			}
		}
	}
	for(int i = len-1 ; i >= 0 ; i--){
		if(cal[i].n >= 10){
			if(i == 0){
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
				cal[i-1].n += (cal[i].n/10);
				cal[i].n %= 10;
			}
		}
	}
	//檢查前面是零(不只一位)，縮減長度
	int tmpcnt = 0;
	for (int i = 0; i < len; ++i)
	{
		if (cal[i].n == 0)
		{
			tmpcnt ++;
		}else{
			break;
		}
	}
	for (int i = tmpcnt; i < len; ++i)
	{
		cal[i-tmpcnt].n = cal[i].n;
	}
	len -= tmpcnt;
	for(int i = 0 ; i < len;i++){
		cal[i].p = len-1-i;
	}
}
string to_string(big_int n){
	string s;
	for (int i = 0; i < n.len; ++i)
	{
		s += char(n.cal[i].n + '0');
	}
	return s;
}