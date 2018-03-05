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
	friend istream& operator>>(istream& in, MyVector& v);
	friend ostream& operator<<(ostream& out, const MyVector& v);
};
ostream& operator<<(ostream& out, const MyVector& v)
{
	out << "(";
	for(int i = 0; i < v.n - 1; i++)
		out << v.m[i] << ", ";
	out << v.m[v.n - 1] << ")";
	return out;
}
istream& operator>>(istream& in, MyVector& v){
	in >> v.n ;
	for(int i = 0; i < v.n; i++)
		in >> v.m[i];
	return in;
}
int main(){
	double d = 1.23;
	double m[3] = {-d, -d, -d};
	MyVector v(3, m);
	cout << v;
	cin >> v;
	cout << v;
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

