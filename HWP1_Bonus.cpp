#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
using namespace std;

static int vcnt = 0;
class Myvector
{
private:

public:
	Myvector();
	void operator=(Myvector q);
	// Myvector operator+();
	// Myvector operator-();
	// void operator[](int n,int value);
	// Myvector operator<();
	bool operator>(Myvector q);
	bool operator==(Myvector q);
	// void print();
	~ Myvector();
	//------------------
	vector<int> v;
	string id;
	int real_len;
	//------------------
	friend void declare(Myvector ** ptr);
	friend int main();
};
void declare(Myvector **ptr);
void assign(Myvector **ptr,string name);
bool compare(Myvector **ptr);

/*
N a 3 0 0 0
N b 3 0 0 0
C E a b 
A a 8 3 4 3 4 3 4 5 6
C E a b
C G a b
C L a b
N c 2 -1 -2
C L c b
C L a c

S 4 a a b c
I a 1 0

*/
//1
//0
//1
//1
//0
//0

int main()
{

	Myvector** ptr;
	ptr = new Myvector* [100];
	char c;

	string _name;
	while(cin >> c){
		switch(c){
			case 'N'://declare
				declare(ptr);
				break;
			case 'A'://assignment
				cin >> _name;
				assign(ptr,_name);
				break;
			case 'C'://comparison
				cout << compare(ptr)<<"\n";
				break;
			case 'I'://indexing
				break;
			case 'S'://sum
				break;
			case 'M'://minus
				break;
		}
		// ptr[vcnt]-> print();
		// cout << "-------\n";
	}
	
	return 0;
}
bool Myvector::operator>(Myvector q){
	int gap;
	gap = this->real_len - q.real_len;
	gap = abs(gap);
	if (this->real_len > q.real_len)
	{
		for (int i = 0; i < gap; ++i)
		{
			q.v.push_back(q.v[i%real_len]);
		}

	// cout << "--------\n";
	// this->print();
	// for (int i = 0; i < this->real_len; ++i)
	// {
	// 	cout << q.v[i] <<" ";
	// }
	// cout << endl;
	// cout << "----------\n";
		for (int i = 0; i < this->real_len; ++i)
		{
			if (this->v[i] < q.v[i])
			{
				return false;
			}
		}
	}else if (this->real_len < q.real_len)
	{
		for (int i = 0; i < gap; ++i)
		{
			this->v.push_back(this->v[i % real_len]);
		}
	// cout << "--------\n";
	// for (int i = 0; i < q.real_len; ++i)
	// {
	// 	cout << this->v[i] << " ";
	// }
	// cout <<endl; 
	// q.print();
	// cout << "----------\n";
		for (int i = 0; i < q.real_len; ++i)
		{
			if (this->v[i] < q.v[i])
			{
				return false;
			}
		}
	}
	for (int i = 0; i < q.real_len; ++i)
	{
		if (this->v[i] < q.v[i])
		{
			return false;
		}
	}
	return true;
}
bool compare(Myvector **ptr){
	char op;
	cin >> op;
	string A,B;
	cin >> A;
	cin >> B;
	Myvector sub ,d;
	for (int i = 0; i < vcnt; ++i)
	{
		if (ptr[i]->id == A)
		{
			sub = *ptr[i];
		}else if (ptr[i]->id == B)
		{
			d = *ptr[i];
		}
	}
	switch(op){
		case 'L':
			if (sub > d || sub == d){
				return false;
			}else{
				return true;
			}
		case 'G':
			return sub > d;
		case 'E':
			return sub == d;
	}
	return 0;
}
void assign(Myvector **ptr,string name){
	int numcnt;
	cin >> numcnt;
	for (int i = 0; i < vcnt; ++i)
	{
		if (ptr[i]->id == name)
		{
			ptr[i]->v.clear();
			ptr[i]->real_len = numcnt;
			for (int j = 0; j < numcnt; ++j)
			{
				int tmp;
				cin >> tmp;
				ptr[i]->v.push_back(tmp);
			}
			// ptr[i]->print();
			break;
		}
	}

}


void declare(Myvector **ptr){
	string name;
	int count;
	// cout << "declare\n";
	cin >> name;
	cin >> count;
	ptr[vcnt] = new Myvector();
	ptr[vcnt]->id = name;
	ptr[vcnt]->real_len = count;
	for (int i = 0; i < count; ++i)
	{
		int tmp;
		cin >> tmp;
		ptr[vcnt]->v.push_back(tmp);
	}
	vcnt ++;
}

Myvector::Myvector(){
	id = "";
	real_len = 0;
}
Myvector::~Myvector(){

}
void Myvector::operator=(Myvector q){
	this->v = q.v;
	this->real_len = q.real_len;
	this->id = q.id;//--------------------
}

bool Myvector::operator==(Myvector q){
	if (this->real_len != q.real_len)
	{
		return false;
	}
	if (this->v == q.v)
	{
		return true;
	}else{
		return false;
	}
}
// void Myvector::operator[](int n,int value){
// 	this->v[n] = value;
// }
// void Myvector::print(){
// 	cout << "id: " << id << endl;
// 	cout << "len:" << real_len << endl; 
// 	for (int i = 0; i < real_len; ++i)
// 	{
// 		cout << v[i] << " ";
// 	}
// 	cout << endl;
// }