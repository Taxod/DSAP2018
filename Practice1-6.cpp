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
	MyVector operator-(Myvector& v);
};

int main(){
	double d = 1.23;
	double m[3] = {-d, -d, -d};
	MyVector v(3, m);
	v.print();
	v = -v;
	v.print();
	if(v == d)
		cout << "Equal!";
	else
		cout << "Unequal!";
	return 0;
}

MyVector MyVector::operator-(Myvector& v){
	MyVector t(v);
	for(int i = 0 ; i < t.n ; i++){
		t.m[i] = -t.m[i];
	}
	return t;
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
