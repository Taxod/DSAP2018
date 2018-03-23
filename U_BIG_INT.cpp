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
		big_int operator-();
		big_int operator*(big_int q);//�P�U
		big_int operator/(big_int q);//�B�z���t��
		big_int operator/(int n);
		big_int operator%(big_int q);
		int operator[](int n);
		bool operator>(big_int q);
		bool operator<(big_int q);
		bool operator==(big_int q);
		bool isPrime();//�]�Ӥ[�ݭn�ץ�
		void operator=(big_int q);
		void operator=(string s);
		big_int abs();//�ۨ��n���n����
		big_int square();
		void check();
		void print();
		big_int merge(const big_int q);
		// friend main();//�O�o�R��------------
		friend ostream& operator<<(ostream& out,const big_int& q);
		friend istream& operator>>(istream& in,const big_int& q);
		
};
string to_string(big_int n);
//string to_string(int n);
ostream& operator<<(ostream& out,const big_int& q);
istream& operator>>(istream& in,big_int& q);
// big_int calculate(string cs,big_int** ptr);
big_int find_object(string s,int nameCnt,big_int** ptr,string name[]);

big_int calculate(string cs, big_int** ptr,string name[],int nameCnt);































































int main(){
	string cs;
	string name[20];
	int nameCnt = 0;
	big_int **BIGP = new big_int* [20];
	while(getline(cin,cs)){
		if (cs.find_last_of(";") != string::npos)
		{
			cs.erase(cs.find_last_of(";"));
		}
		if (cs.find("int") != string::npos)
		{
			// cout << "declare!!!\n";
			cs.erase(0,4);
			name[nameCnt] = cs.substr(0,cs.find(" "));
			cs.erase(0,name[nameCnt].length()+3);
			// cout << cs<<"//\n";
			BIGP[nameCnt] = new big_int(cs);
			nameCnt++;
		}else if(cs.find("BigInt") != string::npos){
			cs.erase(0,7);
			name[nameCnt] = cs.substr(0,cs.find(" "));
			cs.erase(0,name[nameCnt].length()+3);
			// cout << cs<<"//\n";
			BIGP[nameCnt] = new big_int(cs);
			nameCnt++;
		}else if (cs.find("cout") != string::npos)
		{    // ���S�w�ȡB�P�_���------------------------
			// cout << "print!!!\n";
			cs.erase(0,8);
			for (int i = 0; i < nameCnt; ++i)
			{	
				if (name[i] == cs)
				{
					cout << *BIGP[i];//�o���O����-------
					// BIGP[i]->print();
				}
			}
		}else{
			size_t found = cs.find(" ",0);
			int spaceCnt = 0;
			while(found != string::npos){
				spaceCnt ++;
				found = cs.find(" ",found+1);
			}
			if (spaceCnt == 2)
			{
				if (cs.find(".abs()") != string::npos)//�����
				{
					// cout << "abs!!!\n";
					string target = cs.substr(0,cs.find(" "));
					cs.erase(0,cs.find(" ")+3);
					string base = cs.substr(0,cs.find("."));
					for (int i = 0; i < nameCnt; ++i)
					{
						if (name[i] == target)
						{
							*BIGP[i] = find_object(base,nameCnt,BIGP,name).abs();
						}
					}
					/*k = m.abs();*/
				}else if (cs.find(".squre()") != string::npos)//����
				{
					string target = cs.substr(0,cs.find(" "));
					cs.erase(0,cs.find(" ")+3);
					string base = cs.substr(0,cs.find("."));
					for (int i = 0; i < nameCnt; ++i)
					{
						if (name[i] == target)
						{
							*BIGP[i] = find_object(base,nameCnt,BIGP,name).square();
						}
					}
					/*k = m.square()*/
				}else{//�ۤϼ�
					// cout << "-!!!\n";
					string target = cs.substr(0,cs.find(" "));
					cs.erase(0,cs.find(" ")+4);
					string base = cs;
					for (int i = 0; i < nameCnt; ++i)
					{
						if (name[i] == target)
						{
							*BIGP[i] = -(find_object(base,nameCnt,BIGP,name));
						}
					}
					/*m = -m;*/
				}
			}else if (spaceCnt == 4)//�B��
			{
				string target = cs.substr(0,cs.find(" "));
				cs.erase(0,cs.find(" ")+3);
				for (int i = 0; i < nameCnt; ++i)
				{
					if (name[i] == target)
					{
						*BIGP[i] = calculate(cs,BIGP,name,nameCnt);
						// cout << *BIGP[i] << "*\n";
					}
				}
			}else{
				cout <<"error!!\n";
			}

		}
	}
	for (int i = 0; i < 20; ++i)
	{
		delete BIGP[i];
	}
	delete [] BIGP;
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
		out << "-";
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
bool big_int::isPrime(){
	big_int tmp = *this;
	big_int zero;
	zero = "0";
	big_int one;
	one = "1";
	big_int i;
	for (i = "0"; i < tmp; i = i + one)
	{
		if (*this % i == zero)
		{
			return false;
		}
	}
	return true;
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
	subd = subd.abs();
	d = d.abs();
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

big_int big_int::operator+(big_int q){//�ݭn�ק�
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
		//�����D���̥X��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
				len++;//��s����
				//��s���
				for(int i = 0 ; i < len;i++){
					cal[i].p = len-1-i;
				}
			}else{
				cal[i-1].n += (cal[i].n/10);
				cal[i].n %= 10;
			}
		}
	}
	//�ˬd�e���O�s(���u�@��)�A�Y�����
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
//string to_string(int n){
//	int count = 0;
//	string s;
//	int t = n;
//	while (t/=10){
//		count++;	
//	} 
//	for(int i = 0 ; i < count+1 ; i++){
//		s += '0';
//	}
//	while( n > 0){
//		s[count] = char(n%10 +'0');
//		count --; 
//		n /= 10;
//	} 
//	return s;
//}
