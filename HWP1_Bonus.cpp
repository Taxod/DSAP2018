#include <vector>
#include <iostream>
#include <String>
using namespace std;

class Myvector
{
private:
	vector<int> v;
	string id;
	int real_len;
public:
	Myvector();
	void operator=(Myvector q);
	// Myvector operator+();
	// Myvector operator-();
	// void operator[](int n,int value);
	// Myvector operator<();
	// Myvector operator>();
	bool operator==(Myvector q);
	~ Myvector();
	friend void declare(Myvector ** ptr,int vcnt);
};
void declare(Myvector **ptr,int vcnt);


int main(int argc, char const *argv[])
{
	Myvector** ptr;
	ptr = new Myvector* [100];
	int vcnt = 0;
	char c;
	while(cin >> c){
		switch(c){
			case 'N'://declare
				declare(ptr,vcnt);
				break;
			case 'A'://assignment
				break;
			case 'C'://comparison
				break;
			case 'I'://indexing
				break;
			case 'S'://sum
				break;
			case 'M'://minus
				break;
		}
	}
	
	return 0;
}



void declare(Myvector **ptr,int vcnt){
	string name;
	cin >> name;
	ptr[vcnt] = new Myvector();
	ptr[vcnt]->id = name;
	int count;
	ptr[vcnt]->real_len = count;
	cin >> count;
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
	// this->id = q.id;--------------------
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