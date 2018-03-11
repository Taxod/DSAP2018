#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<string>
using namespace std;
class MyVector
{
private:
	int n;
	double* m;
public:
	MyVector();
	MyVector(int n, double m[]);
	MyVector(const MyVector& v);
	~MyVector();
	void print();
};
istream& operator >>(istream& in, MyVector& v){
	string p;
	getline(in,p,',');
}
int main(){
	string p;
	getline(cin,p);
	int count = 0;
	size_t ptr = p.find(',');
	while((p+ptr).find(',')!=string::npos){
		count++;
		ptr++;
//		cout << "bfb";
	}
	cout << count;
//	char* ptr = strtok(p,',');
//	cout << p[3];
	/*double d[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	MyVector u(5, d);
	cin >> u;
	u.print();*/
	return 0;
}

MyVector::MyVector()
{
	n = 0;
	m = nullptr;
}

MyVector::MyVector(int dim, double v[])
{
	n = dim;
	m = new double[dim];
	for(int i = 0; i < dim; i++)
	m[i] = v[i];
}

MyVector::~MyVector()
{
	delete [] m;
}

MyVector::MyVector(const MyVector& v)
{
	n = v.n;
	m = new double[n];
	for(int i = 0; i < n; i++)
		m[i] = v.m[i];
}

void MyVector::print()
{
	cout << "(";
	for(int i = 0; i < n - 1; i++)
		cout << m[i] << ", ";
	cout << m[n-1] << ")\n";
}

