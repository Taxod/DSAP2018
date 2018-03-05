#include<iostream>

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

int main(){
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
