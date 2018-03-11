#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<string>
using namespace std;
class MyVector
{
friend istream& operator >>(istream& in, MyVector& v);
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
	char p[10000]={0};
	cin.getline(p,10000);
	int count = 0;
	char* ptr = strchr(p, ',');
	while(ptr != nullptr)
	{
		*ptr = '_';
		ptr = strchr(ptr, ',');
		count ++;
	}
	ptr = strchr(p, '<');
	*ptr = '_';
	ptr = strchr(p, '>');
	*ptr = '_';
	double* num = new double [count+1];
	int wordcnt = 0;
	char delim = '_';
	char* start = strtok(p, &delim);
	char temp[1000] ={0};
	while(start != nullptr)
	{
		strcpy(temp, start);
		num[wordcnt] = atoi(temp);
		wordcnt++;
		start = strtok(nullptr, &delim);
	}
	delete [] v.m ;
	v.n = count + 1;
	v.m = new double [v.n];
	for(int i = 0 ; i < v.n; i++){
		v.m[i] = num[i];
	}
}
int main(){
	double d[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	MyVector u(5, d);
	cin >> u;
	u.print();
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

