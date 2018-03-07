#include<iostream>
#include<cstring>
#include<stdlib.h>
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
	bool operator==(const double d) const;
	double operator[](int i, int j) const;

};
double MyVector::operator[](int i, int j) const{




}
int main(){
	double d[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	MyVector v(5, d);
	cout << v[1, 3];
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
bool MyVector::operator==(const double d) const
{
	for(int i = 0; i < n; i++) {
		if(this->m[i] - d > 0.00001)
			return false;
	}
	return true;
}

