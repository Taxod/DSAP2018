#include<iostream>
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
	const MyVector operator+(const MyVector& v) const;
};

const MyVector MyVector::operator+(const MyVector& v) const{
	//判斷數字個數、大小 
	if(n == v.n){
		int p = n;
		double* q = new double [n];
		for(int i = 0 ; i < n ;i++){
			q[i] = m[i]+v.m[i];
		}
		MyVector result(p,q);
		return result;
	}else if(n < v.n){
		int p = v.n;
		double* q = new double [v.n];
		for(int i = 0 ; i < v.n ;i++){
			q[i] = m[i%n] + v.m[i];
		}
		MyVector result(p,q);
		return result;
	}else{
		int p = n;
		double* q = new double [n];
		for(int i = 0 ; i < n ;i++){
			q[i] = m[i] + v.m[i%v.n];
		}
		MyVector result(p,q);
		return result;
	}
}

int main(){
	double d[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	MyVector u(5, d);
	double f[2] = {1.1, 2.2};
	MyVector v(2, f);
	MyVector w = u + v;
	w.print();
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
