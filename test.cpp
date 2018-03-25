#include<iostream>
#include<string>
#include <stdlib.h>
#include<math.h>
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
		big_int operator-();
		big_int operator*(big_int q);
		big_int operator/(big_int q);
		big_int operator/(int n);
		big_int operator%(big_int q);
		int operator[](int n);
		bool operator>(big_int q);
		bool operator<(big_int q);
		bool operator==(big_int q);
		bool isPrime();//跑太久需要修正
		void operator=(big_int q);
		void operator=(string s);
		big_int abs();
		big_int square();
		void check();
		void print();
		big_int merge(const big_int q);
		friend ostream& operator<<(ostream& out,const big_int& q);
		friend istream& operator>>(istream& in,const big_int& q);
		
};
string to_string(big_int n);
//string to_string(int n);
ostream& operator<<(ostream& out,const big_int& q);
istream& operator>>(istream& in,big_int& q);
big_int find_object(string s,int nameCnt,big_int** ptr,string name[]);
big_int calculate(string cs, big_int** ptr,string name[],int nameCnt);

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






























































int main(){
	string y ="17";
	big_int i(y);
	string h ="17";
	big_int j(h);
	string k = "0";
	big_int u(k);
	string r = "14";
	big_int R (r);
	// cout << i[5];
	cout << i / j;
	// cout << i.isPrime();
	// int ii = -11;
	// int jj = -12;
	// cout << ii%jj<<"//\n";
	// cout << i;//120
	// cout << j;//11
	// cout << u;//0
	// cout << R;//3
	// cout << j%i;//10
	// cout << i.isPrime();
	// cout << i;
	return 0;
}

























































big_int find_object(string s,int nameCnt,big_int** ptr,string name[]){
	big_int result;
	if (s.find_first_of("0123456789") != string::npos)
	{
		result = s;
	}else{
		for (int i = 0; i < nameCnt; ++i)
		{
			if (name[i] == s)
			{
				result = *ptr[i];
			}
		}
	}
	return result;
}

big_int calculate(string cs, big_int** ptr,string name[],int nameCnt){
	big_int subop;
	big_int op;
	string c;
	string tmpname;
	tmpname = cs.substr(0,cs.find(" "));
	cs.erase(0,tmpname.length()+1);
	c = cs.substr(0,1);
	cs.erase(0,2);
	// cout << tmpname << ":"<< c <<":" <<cs<<endl;
	subop = find_object(tmpname,nameCnt,ptr,name);
	op = find_object(cs,nameCnt,ptr,name);
	char o = c[0];
	switch(o){
		case '+':
			return (subop + op);
			break;
		case '-':
			return (subop - op);
			break;
		case '*':
			return (subop * op);
			break;
		case '/':
			return (subop / op);
			break;
		case '%':
			return (subop % op);
	}
	return subop;
}

istream& operator>>(istream& in,big_int& q){
	string tmp;
	in >> tmp;
	big_int t(tmp);
	q = t;
	return in;
}
ostream& operator<<(ostream& out, const big_int& q){
	if (q.negative)
	{
		if (q.len == 1 && q.cal[0].n == 0)
		{
			/* code */
		}else{
			out << "-";	
		}
		
	}
	for (int i = 0; i < q.len; ++i)
	{
		out << q.cal[i].n;
	}
	out <<endl;
	return out;
}




big_int big_int::operator-(){
	big_int result(*this);
	if (result.negative == false)
	{
		result.negative = true;
	}else{
		result.negative = false;
	}
	// cout << "operator-";
	return result;
}
int big_int::operator[](int n){
	big_int tmp = this->abs();
	int result = tmp.cal[tmp.len - n-1].n;
	return result;
}
big_int big_int::operator/(int n){
	big_int tmp;
	tmp = to_string(n);
	big_int result = *this / tmp;
	return result;
}
// big_int big_int::operator%(int n){
// 	big_int tmp;
// 	tmp = to_string(n);
// 	big_int result = *this % tmp;
// 	return result;	
// }
bool big_int::isPrime(){
	big_int zero;
	zero = "0";
	big_int one;
	one = "1";
	big_int two;
	two = "2";

	big_int tmp = *this;
	if (*this == one || *this == two)
	{
		return true;
	}
	if (this->cal[this->len-1].n % 2 == 0)
	{
		return false;
	}else if ((this->cal[this->len-1].n + this->cal[this->len-2].n) % 3 == 0)
	{
		return false;
	}else{
		big_int i;
		for ( i = "2"; i < *this; i = i + one)
		{
			cout << "*"<<i ;
			if (*this % i == zero)
			{
				return false;
			}
			if (!(i == two))
			{
				i = i + one;
			}
		}
		return true;
	}
	return true;
}
void big_int::operator=(string s){
	big_int p(s);
	*this = p;
}
big_int big_int::operator/(big_int q){
	big_int result;
	big_int subd(*this);
	big_int d(q);
	subd = subd.abs();
	d = d.abs();
	result = "0";
	// cout << "---";
	if (d > subd)
	{
		// result = "0";
		return result;
	}
	// cout << "---";
	string tmpd;
	for (int i = 0; i < d.len; ++i)
	{
		tmpd += (d.cal[i].n+'0');
	}
	int count = 0;
	for (int i = 0; i < subd.len-d.len; ++i)
	{
		tmpd.insert(tmpd.length(),"0");
		count++;
	}
	// cout << tmpd<<"*\n";
	big_int bd(tmpd);
	while(subd > d || subd == d){
		if (subd > bd || subd == d)
		{
			subd = subd - bd;
			string ans = "1";
			for (int i = 0; i < count; ++i)
			{
				// cout <<ans<<";";
				ans.insert(ans.length(),"0");
				// cout << ans<<"\n";
			}
			big_int A(ans);
			// cout << A;
			result = result + A;
		}else{
			tmpd = tmpd.substr(0,tmpd.length()-1);
			bd = tmpd;
			count--;
			if (count < 0)
			{
				break;
			}
		}
	}
	if (this->negative != q.negative)
	{
		result.negative = true;
	}
	return result;
}

big_int big_int::operator%(big_int q){
	big_int result;
	big_int subd(*this);
	big_int d(q);
	if (subd.abs() < d.abs())
	{
		result = subd;
		return result;
	}
	big_int ans;
	ans = subd.abs() / d.abs();
	ans = ans * d.abs();
	result = subd.abs() - ans;
	if (subd.negative == true)
	{
		result.negative = true;
	}else{
		result.negative = false;
	}
	return result;
}

big_int big_int::operator-(big_int q){
	big_int result;
	big_int subm;
	big_int m;
	big_int zero;
	zero = "0";
	if (*this == q)
	{
		return zero;
	}
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
		}else{
			result.negative = false;
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
		}else{
			result.negative = false;
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

big_int big_int::operator+(big_int q){
	big_int result;
	big_int zero;
	zero = "0";
	result = zero;
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
		if (this->abs() == q.abs())
		{
			return zero;
		}else if (this->abs() > q.abs())
		{
			for (int i = 0; i < q.len; ++i)
			{
				q.cal[i].n *= -1;
			}
			result = this->merge(q);
			for (int i = 0; i < q.len; ++i)
			{
				q.cal[i].n *= -1;
			}
			if (this->negative == true)
			{
				result.negative = true;
			}else{
				result.negative = false;
			}
			return result;
		}else{
			for (int i = 0; i < this->len; ++i)
			{
				this->cal[i].n *= -1;
			}
			result = this->merge(q);
			for (int i = 0; i < this->len; ++i)
			{
				this->cal[i].n *= -1;
			}
			if (q.negative == true)
			{
					result.negative = true;
			}else{
				result.negative = false;
			}
			return result;
		}
	}	
}
big_int big_int::merge(big_int q){
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
	big_int zero;
	zero = "0";
	if (*this == zero || q == zero)
	{
		result = zero;
		return result;
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
	if (this->negative != q.negative)
	{
			result.negative = true;		
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
		// char temp = num[i];
		// cal[i].n = atoi(&temp);
		//不知道哪裡出錯!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		cal[i].n = int(num[i]-'0');
		cal[i].p = len-1-i;
	}

}
big_int::~big_int(){
}

void big_int::print(){
	for(int i = 0 ; i < len ; i++){
		cout << "-"<<cal[i].n << "-";
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
big_int big_int::square(){
	big_int result(*this);
	result = result * result;
	result.negative = false;
	return result;
}
void big_int::check(){
	big_int zero;
	zero = "0";
	if (!(*this == zero))
	{
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
	
}
string to_string(big_int n){
	string s;
	for (int i = 0; i < n.len; ++i)
	{
		s += char(n.cal[i].n + '0');
	}
	return s;
}

